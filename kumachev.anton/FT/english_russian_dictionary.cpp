#include "english_russian_dictionary.h"
#include <iostream>

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

static bool isEnglishWord(const char *string)
{
  return (*string >= 'a' && *string <= 'z') || (*string >= 'A' && *string <= 'Z');
}

void kumachev::EnglishRussianDictionary::read(std::istream &istream)
{
  std::string english;
  std::string buffer;

  while (istream.good() && !istream.eof()) {
    istream >> buffer;

    if (istream.fail()) {
      break;
    }

    if (isEnglishWord(buffer.c_str())) {
      english = buffer;

      if (map_.find(english) == map_.end()) {
        map_.emplace(english, std::vector< std::string >{});
      }
    } else {
      if (english.empty()) {
        istream.setstate(std::ios::failbit);
        return;
      }

      map_[english].push_back(buffer);
    }
  }
}

void kumachev::EnglishRussianDictionary::write(std::ostream &ostream)
{
  for (const auto &eng: map_) {
    ostream << eng.first << ' ';

    for (const auto &rus: eng.second) {
      ostream << rus << ' ';
    }

    ostream << '\n';
  }
}

kumachev::EnglishRussianDictionary::EnglishRussianDictionary() = default;
