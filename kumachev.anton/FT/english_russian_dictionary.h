#ifndef FT_ENGLISH_RUSSIAN_DICTIONARY_H
#define FT_ENGLISH_RUSSIAN_DICTIONARY_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "word_not_found_exception.h"

namespace kumachev {
  template< class Map >
  class EnglishRussianDictionary {
  public:
    using not_found_exception = kumachev::WordNotFound;
    EnglishRussianDictionary();

    template< class IITer >
    void add(const std::string &english, IITer begin, IITer end);

    void clear();
    const std::vector< std::string > &translate(const std::string &english);

  private:
    Map map_;
  };
}

template< class Map >
kumachev::EnglishRussianDictionary< Map >::EnglishRussianDictionary() = default;

template< class Map >
template< class IIter >
void kumachev::EnglishRussianDictionary< Map >::add(const std::string &english, IIter begin, IIter end)
{
  auto &coll = map_[english];
  auto insert = std::back_inserter(coll);
  std::copy(begin, end, insert);
  std::sort(coll.begin(), coll.end());
}

template< class Map >
void kumachev::EnglishRussianDictionary< Map >::clear()
{
  map_.clear();
}

template< class Map >
const std::vector< std::string > &kumachev::EnglishRussianDictionary< Map >::translate(const std::string &english)
{
  if (map_.find(english) != map_.end()) {
    return map_[english];
  }
  else {
    throw not_found_exception();
  }
}

#endif //FT_ENGLISH_RUSSIAN_DICTIONARY_H
