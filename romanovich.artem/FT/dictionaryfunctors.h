#ifndef DICTIONARYFUNCTORS_H
#define DICTIONARYFUNCTORS_H
#include <string>
#include <utility>
#include "hashtable.h"
namespace romanovich
{
  struct DictionaryNameEqual
  {
    const std::string &targetName;
    explicit DictionaryNameEqual(const std::string &name):
      targetName(name)
    {
    }
    bool operator()(const std::pair< std::string, HashTable > &pair) const
    {
      return pair.first == targetName;
    }
  };
  struct NonEmptyString
  {
    bool operator()(const std::string &str) const
    {
      return !str.empty();
    }
  };
  struct NonEmptyWord
  {
    bool operator()(const WordEntry &entry) const
    {
      return !entry.word.empty();
    }
  };
  struct WordToString
  {
    std::string operator()(const WordEntry &entry) const
    {
      return entry.word;
    }
  };
  struct CountTranslations
  {
    size_t operator()(size_t accumulator, const WordEntry &entry) const
    {
      return accumulator + entry.translations.size();
    }
  };
}
#endif
