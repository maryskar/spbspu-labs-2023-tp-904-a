#ifndef FT_DICTIONARY_HPP
#define FT_DICTIONARY_HPP
#include <iostream>
#include <map>
#include <string>

namespace vagina
{
  struct dictionary
  {
    std::map< std::string, size_t > dict_;
    void insert(const std::string& word);
    bool empty() const;
  };
  using dictionaryOfNames = std::map < std::string, dictionary >;
  dictionary& findSpecificDict(dictionaryOfNames&, std::string& name);
  const dictionary& findSpecificDict(const dictionaryOfNames& dicts, std::string& name);
}

#endif
