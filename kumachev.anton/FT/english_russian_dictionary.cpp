#include "english_russian_dictionary.h"

void kumachev::EnglishRussianDictionary::clear()
{
  map_.clear();
}

const std::vector< std::string > &kumachev::EnglishRussianDictionary::translate(const std::string &english)
{
  if (map_.find(english) != map_.end()) {
    return map_[english];
  } else {
    throw not_found_exception();
  }
}

kumachev::EnglishRussianDictionary::EnglishRussianDictionary() = default;