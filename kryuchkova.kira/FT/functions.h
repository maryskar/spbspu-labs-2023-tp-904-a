#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "dictionary.h"

namespace kryuchkova
{
  void doCreate(std::istream & in, std::map< std::string, ErDictionary > & dicts);
  void doInsert(std::istream & in, ErDictionary & dict);
  void doSearch(std::istream & in, std::ostream & out, const ErDictionary & dict);
  void doDelete(std::istream & in, ErDictionary & dict);
  void fillDict(std::istream & in, ErDictionary & dict);
  void findByFirstLet(std::istream & in, std::ostream & out, ErDictionary & dict);
  void printDict(std::ostream & out, const ErDictionary & dict);
  void exportDict(std::istream & in, ErDictionary & dict);
  void unite(const ErDictionary & dict1, const ErDictionary & dict2);
  void intersect(const ErDictionary & dict1, const ErDictionary & dict2);
  void symSubtract(const ErDictionary & dict1, const ErDictionary & dict2);
  void subtract(const ErDictionary & dict1, const ErDictionary & dict2);
  bool addition(const ErDictionary & dict1, const ErDictionary & dict2);

}

#endif
