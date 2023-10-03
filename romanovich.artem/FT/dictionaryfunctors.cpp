#include "dictionaryfunctors.h"
romanovich::DictionaryNameEqual::DictionaryNameEqual(const std::string &name):
  targetName(name)
{
}
bool romanovich::DictionaryNameEqual::operator()(const std::pair< std::string, HashTable > &pair) const
{
  return pair.first == targetName;
}
bool romanovich::NonEmptyString::operator()(const std::string &str) const
{
  return !str.empty();
}
bool romanovich::NonEmptyWord::operator()(const romanovich::WordEntry &entry) const
{
  return !entry.word.empty();
}
std::string romanovich::WordToString::operator()(const romanovich::WordEntry &entry) const
{
  return entry.word;
}
size_t romanovich::CountTranslations::operator()(size_t accumulator, const romanovich::WordEntry &entry) const
{
  return accumulator + entry.translations.size();
}
romanovich::TranslateCopier::TranslateCopier(std::vector< std::string > &result):
  result_(result)
{
}
std::vector< std::string > &romanovich::TranslateCopier::operator()(std::vector< std::string > &result,
    const romanovich::WordEntry &wordEntry)
{
  std::copy_if(wordEntry.translations.begin(),
      wordEntry.translations.end(), std::back_inserter(result), NonEmptyString());
  return result;
}
