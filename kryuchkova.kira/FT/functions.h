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
  void findByFirstLet(std::istream & in, ErDictionary & dict);
  void printDict(std::ostream & out, const ErDictionary & dict);
  void exportDict(std::istream & in, ErDictionary & dict);
  void unite(ErDictionary new_dict, const ErDictionary & dict1, const ErDictionary & dict2);
  void intersect(ErDictionary new_dict, const ErDictionary & dict1, const ErDictionary & dict2);
  void symSubtract(ErDictionary new_dict, const ErDictionary & dict1, const ErDictionary & dict2);
  void subtract(ErDictionary new_dict, const ErDictionary & dict1, const ErDictionary & dict2);
  void addition(const ErDictionary & dict1, const ErDictionary & dict2);

}

#endif
