#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "dictionary.h"

namespace kryuchkova
{
  void doCreate(std::istream & in, std::map< std::string, ErDictionary > & dicts);
  void doInsert(std::istream & in, std::map< std::string, ErDictionary > & dicts);
  void doSearch(std::istream & in, std::ostream & out, const std::map< std::string, ErDictionary > & dicts);
  void doDelete(std::istream & in, std::map< std::string, ErDictionary > & dicts);
  void fillDict(std::istream & in, std::map< std::string, ErDictionary > & dicts);
  void findByFirstLet(std::istream & in, std::ostream & out, const std::map< std::string, ErDictionary > & dicts);
  void printDict(std::istream & in, std::ostream & out, const std::map< std::string, ErDictionary > & dicts);
  void exportDict(std::istream & in, const std::map< std::string, ErDictionary > & dicts);
  void unite(std::istream & in, std::map< std::string, ErDictionary > & dicts);
  void intersect(std::istream & in, std::map< std::string, ErDictionary > & dicts);
  void symSubtract(std::istream & in, std::map< std::string, ErDictionary > & dicts);
  void subtract(std::istream & in, std::map< std::string, ErDictionary > & dicts);
  void addition(std::istream & in, std::ostream & out, std::map< std::string, ErDictionary > & dicts);
}

#endif
