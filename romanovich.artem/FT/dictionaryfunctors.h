#ifndef DICTIONARYFUNCTORS_H
#define DICTIONARYFUNCTORS_H
#include <string>
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
}
#endif
