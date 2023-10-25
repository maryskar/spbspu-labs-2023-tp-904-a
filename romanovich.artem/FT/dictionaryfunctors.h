#ifndef DICTIONARYFUNCTORS_H
#define DICTIONARYFUNCTORS_H
#include <string>
#include <utility>
#include <algorithm>
#include "hashtable.h"
namespace romanovich
{
  struct DictionaryNameEqual
  {
    const std::string &targetName;
    explicit DictionaryNameEqual(const std::string &name);
    bool operator()(const std::pair< std::string, HashTable > &pair) const;
  };
  struct NonEmptyString
  {
    bool operator()(const std::string &str) const;
  };
  struct NonEmptyWord
  {
    bool operator()(const WordEntry &entry) const;
  };
  struct WordToString
  {
    std::string operator()(const WordEntry &entry) const;
  };
  struct CountTranslations
  {
    size_t operator()(size_t accumulator, const WordEntry &entry) const;
  };
  struct TranslateCopier
  {
    explicit TranslateCopier(std::vector< std::string > &result);
    std::vector< std::string > &operator()(std::vector< std::string > &result, const WordEntry &wordEntry);
    std::vector< std::string > &result_;
  };
}
#endif
