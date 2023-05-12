#ifndef ENGLISH_RUSSIAN_DICTIONARY
#define ENGLISH_RUSSIAN_DICTIONARY

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "word_not_found_exception.h"

namespace kumachev {
  class EnglishRussianDictionary {
  public:
    using not_found_exception = kumachev::WordNotFound;
    EnglishRussianDictionary();

    template< class IITer >
    void add(const std::string &english, IITer begin, IITer end);

    void clear();
    const std::vector< std::string > &translate(const std::string &english);

    void write(std::ostream &ostream);
    void read(std::istream &istream);

  private:
    std::map< std::string, std::vector< std::string > > map_;
  };
}

template< class IIter >
void kumachev::EnglishRussianDictionary::add(const std::string &english, IIter begin, IIter end)
{
  auto &coll = map_[english];
  auto insert = std::back_inserter(coll);
  std::copy(begin, end, insert);
  std::sort(coll.begin(), coll.end());
}

#endif //ENGLISH_RUSSIAN_DICTIONARY
