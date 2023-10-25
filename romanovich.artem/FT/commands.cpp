#include <limits>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <printmessages.h>
#include "commands.h"
#include "dictionaryfunctors.h"
romanovich::CommandHandler::CommandHandler(std::istream &in, std::ostream &out_):
  dictionaries_(DictionariesVault::instance()),
  in_(in),
  out_(out_)
{
  using namespace std::placeholders;
  processor_["ad"] = std::bind(&CommandHandler::addDict, this);
  processor_["aw"] = std::bind(&CommandHandler::addWordToDict, this);
  processor_["at"] = std::bind(&CommandHandler::addTranslation, this);
  processor_["rmw"] = std::bind(&CommandHandler::removeWord, this);
  processor_["rmt"] = std::bind(&CommandHandler::removeTranslation, this);
  processor_["trans"] = std::bind(&CommandHandler::searchTranslations, this);
  processor_["words"] = std::bind(&CommandHandler::searchWords, this);
  processor_["cw"] = std::bind(&CommandHandler::countWords, this);
  processor_["ct"] = std::bind(&CommandHandler::countTranslations, this);
  processor_["export"] = std::bind(&CommandHandler::exportToFile, this);
  processor_["help"] = std::bind(&CommandHandler::help, this);
  processor_["amw"] = std::bind(&CommandHandler::addMissingWords, this);
  processor_["cld"] = std::bind(&CommandHandler::createLevelDict, this);
  processor_["md"] = std::bind(&CommandHandler::mergeDicts, this);
}
void romanovich::CommandHandler::addWordToDict()
{
  std::string word;
  std::string dictName;
  in_ >> word;
  in_ >> dictName;
  auto it = findDictByName(dictName);
  if (it != dictionaries_->end())
  {
    it->second.addKey(word);
    it->second.print(out_);
  }
}
void romanovich::CommandHandler::addDict()
{
  std::string dictName;
  in_ >> dictName;
  dictionaries_->emplace_back(dictName, HashTable());
  printDicts(out_);
}
void romanovich::CommandHandler::addTranslation()
{
  std::string word;
  std::string dictName;
  std::string translation;
  in_ >> word;
  in_ >> dictName;
  in_ >> translation;
  auto it = findDictByName(dictName);
  if (it != dictionaries_->end())
  {
    it->second.addValue(word, translation);
    it->second.print(out_);
  }
}
void romanovich::CommandHandler::removeWord()
{
  std::string word;
  std::string dictName;
  in_ >> word;
  in_ >> dictName;
  auto it = findDictByName(dictName);
  if (it != dictionaries_->end())
  {
    it->second.removeKey(word);
    it->second.print(out_);
  }
}
void romanovich::CommandHandler::removeTranslation()
{
  std::string word;
  std::string dictName;
  std::string translation;
  in_ >> word;
  in_ >> dictName;
  in_ >> translation;
  auto it = findDictByName(dictName);
  if (it != dictionaries_->end())
  {
    it->second.removeValue(word, translation);
    it->second.print(out_);
  }
}
void romanovich::CommandHandler::searchTranslations()
{
  std::string word;
  std::string dictName;
  in_ >> word;
  in_ >> dictName;
  out_ << "Translations of \"" << word << "\" in dictionary \"" << dictName << "\":\n";
  auto it = findDictByName(dictName);
  if (it == dictionaries_->end())
  {
    return;
  }
  const HashTable &dict = it->second;
  std::vector< std::string > allTranslations;
  TranslateCopier copier(allTranslations);
  std::accumulate(dict.getData().begin(), dict.getData().end(), allTranslations, copier);
  std::copy(allTranslations.begin(), allTranslations.end(), std::ostream_iterator< std::string >(out_, ", "));
  out_ << "\n";
}
void romanovich::CommandHandler::searchWords()
{
  std::string dictName;
  in_ >> dictName;
  out_ << "Words in dictionary \"" << dictName << "\":\n";
  auto it = findDictByName(dictName);
  if (it == dictionaries_->end())
  {
    return;
  }
  HashTable &table = it->second;
  const std::vector< WordEntry > &data = table.getData();
  auto firstNotEmptyWord = std::find_if(data.begin(), data.end(), NonEmptyWord());
  if (firstNotEmptyWord != data.end())
  {
    out_ << firstNotEmptyWord->word;
    std::vector< std::string > words;
    std::transform(firstNotEmptyWord, data.end(), std::back_inserter(words), WordToString());
    std::copy(words.begin(), words.end(), std::ostream_iterator< std::string >(out_, ", "));
  }
  out_ << "\n";
}
void romanovich::CommandHandler::countWords()
{
  std::string dictName;
  in_ >> dictName;
  out_ << "Words count in dictionary \"" << dictName << "\": ";
  auto it = findDictByName(dictName);
  if (it == dictionaries_->end())
  {
    out_ << "0\n";
    return;
  }
  HashTable &table = it->second;
  const std::vector< WordEntry > &data = table.getData();
  size_t count = std::count_if(data.begin() + 1, data.end(), NonEmptyWord());
  out_ << count << "\n";
}
void romanovich::CommandHandler::countTranslations()
{
  std::string dictName;
  in_ >> dictName;
  out_ << "Translations count in dictionary \"" << dictName << "\": ";
  auto it = findDictByName(dictName);
  if (it == dictionaries_->end())
  {
    out_ << "0\n";
    return;
  }
  HashTable &table = it->second;
  const std::vector< WordEntry > &data = table.getData();
  size_t count = std::accumulate(data.begin() + 1, data.end(), 0, CountTranslations());
  out_ << count << "\n";
}
void romanovich::CommandHandler::exportToFile()
{
  std::string fileName;
  in_ >> fileName;
  std::ofstream file(fileName + ".txt");
  printDicts(file);
  file.close();
}
void romanovich::CommandHandler::help()
{
  out_ << "Available commands:\n";
  out_ << "ad <dict> - add a new dictionary\n";
  out_ << "aw <word> <dict> - add a new word to dictionaries\n";
  out_ << "at <word> <dict> <translation> - add a new translation to a word\n";
  out_ << "rmw <word> <dict> - remove a word from dictionaries\n";
  out_ << "rmt <word> <dict> <translation> - remove a translation from a word\n";
  out_ << "w <word> <dict> - search for a word in a dictionary\n";
  out_ << "words <dict> - show all words in a dictionary\n";
  out_ << "cw <dict> - count the number of words in dictionaries\n";
  out_ << "ct <word> <dict> - count the number of translations for a word\n";
  out_ << "export <dict> <file> - export dictionary to a file\n";
  out_ << "help - display available commands\n";
  out_ << "amw <dict-from> <dict-to> - add all missing words from one dictionary to another\n";
  out_ << "cld <level> <dict> - create/update level dictionary\n";
  out_ << "md <dict> - merge dictionaries\n";
}
void romanovich::CommandHandler::addMissingWords()
{
  std::string dictFrom;
  std::string dictTo;
  in_ >> dictFrom;
  in_ >> dictTo;
  auto itFrom = findDictByName(dictFrom);
  auto itTo = findDictByName(dictTo);
  if (itFrom == dictionaries_->end())
  {
    out_ << "Dictionary '" << dictFrom << "' not found.\n";
    return;
  }
  if (itTo == dictionaries_->end())
  {
    out_ << "Dictionary '" << dictTo << "' not found.\n";
    return;
  }
  itTo->second.addWordsFromAnother(itFrom->second);
  out_ << "Added missing words from dictionary '" << dictFrom << "' to dictionary '" << dictTo << "'\n";
}
void romanovich::CommandHandler::createLevelDict()
{
  std::string dict;
  std::string newDictName;
  in_ >> dict;
  in_ >> newDictName;
  std::pair< std::string, romanovich::HashTable > newDict;
  newDict.first = newDictName;
  auto it = findDictByName(dict);
  if (it == dictionaries_->end())
  {
    out_ << "Dictionary '" << dict << "' not found.\n";
    return;
  }
  HashTable hashTable;
  hashTable.addLevelWordsFromAnother(it->second);
  dictionaries_->emplace_back(newDictName, hashTable);
  out_ << "Added level words from dictionary '" << dict << "'\n";
}
void romanovich::CommandHandler::mergeDicts()
{
  std::string dict;
  std::string newDictName;
  in_ >> dict;
  in_ >> newDictName;
  auto it = findDictByName(dict);
  if (it == dictionaries_->end())
  {
    out_ << "Dictionary '" << dict << "' not found.\n";
    return;
  }
  HashTable newDict;
  newDict.addLevelWordsFromAnother(it->second);
  dictionaries_->emplace_back(newDictName, newDict);
  out_ << "Added level words from dictionary '" << dict << "'\n";
}
void romanovich::CommandHandler::printDicts(std::ostream &out)
{
  for (const auto &pair: *dictionaries_)
  {
    pair.second.print(out << "Dict " << pair.first << ":\n");
  }
}
void romanovich::CommandHandler::operator()(const std::string &command)
{
  constexpr auto maxLLSize = std::numeric_limits< std::streamsize >::max();
  try
  {
    processor_[command]();
  }
  catch (...)
  {
    printInvalidCommand(out_) << '\n';
    in_.ignore(maxLLSize, '\n');
  }
}
romanovich::DictionariesVault::value_t::iterator romanovich::CommandHandler::findDictByName(const std::string &dictName)
{
  return std::find_if(dictionaries_->begin(), dictionaries_->end(), romanovich::DictionaryNameEqual(dictName));
}
