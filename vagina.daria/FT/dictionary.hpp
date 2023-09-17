#ifndef FT_DICTIONARY_HPP
#define FT_DICTIONARY_HPP
#include <map>
#include <string>
#include <iostream>

struct dictionary
{
  std::map< std::string, size_t > dict_;
  void insert(const std::string& word);
};
using dictionaryOfNames = std::map < std::string, dictionary >;
dictionary& findSpecificDict(dictionaryOfNames&, std::string& name);
const dictionary& findSpecificDict(const dictionaryOfNames& dicts, std::string& name);

#endif