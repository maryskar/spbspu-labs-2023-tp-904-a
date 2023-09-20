#include "dictionary.hpp"

void vagina::dictionary::insert(const std::string& word)
{
  ++dict_[word];
}
vagina::dictionary& vagina::findSpecificDict(dictionaryOfNames& dicts, std::string& name)
{
  return dicts.at(name);
}
const vagina::dictionary& vagina::findSpecificDict(const dictionaryOfNames& dicts, std::string& name)
{
  return dicts.at(name);
}
bool vagina::dictionary::empty() const
{
  return dict_.empty();
}
