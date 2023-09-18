#include "dictionary.hpp"

void dictionary::insert(const std::string& word)
{
  ++dict_[word];
}
dictionary& findSpecificDict(dictionaryOfNames& dicts, std::string& name)
{
  return dicts.at(name);
}
const dictionary& findSpecificDict(const dictionaryOfNames& dicts, std::string& name)
{
  return dicts.at(name);
}
bool dictionary::empty() const
{
  return dict_.empty();
}
