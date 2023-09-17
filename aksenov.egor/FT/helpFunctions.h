#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H
#include <string>
#include "commands.h"
template < typename Compare >
struct KeysCmp
{
  template < typename T >
  bool operator()(const T& a, const T& b)
  {
    return Compare()(a.first, b.first);
  }
};
template < typename T >
using KeysEqual = KeysCmp< std::equal_to< T > >;
std::string getNextWord(std::string& str, char delimeter = ' ');
ru_vector_t splitStringToTranslation(std::string str);
void outRuList(const ru_vector_t &, std::ostream &, const char *);
void outDict(const dict_t& dict, std::ostream& out, const char *);
bool isValidDict(const std::string& name, const dictOfDicts &dicts);
void prepareString(std::string& str);
bool isValidDicts(const std::vector< std::string >& names, const dictOfDicts &dicts);
std::vector< std::string > getNamesFromString(std::string str);
ru_vector_t intersectRuList(const ru_vector_t& first, const ru_vector_t& second);
dict_t intersectDicts(const dict_t& first, const dict_t& second);

#endif