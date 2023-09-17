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
  struct StringConcatenator
    {
    std::string delimiter_;
    explicit StringConcatenator(std::string del):
    delimiter_(std::move(del))
    {}
    std::string operator()(const std::string& tmp, const std::string& value) const
    {
      return tmp.empty() ? value : tmp + delimiter_ + value;
    }
  };
}
#endif
