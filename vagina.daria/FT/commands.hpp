#ifndef FT_COMMANDS_HPP
#define FT_COMMANDS_HPP
#include <map>
#include <string>
#include <vector>
#include "dictionary.hpp"

namespace vagina
{
  void messageEmptyCommand(std::ostream& out);
  void createSet(dictionaryOfNames& diction, std::istream& in);
  bool isGreater(const std::pair< std::string, size_t >& p1, const std::pair< std::string, size_t >& p2);
  void sortAndPrintFromTheLargest(const dictionary& wordFrequency, std::ostream& out);
  void threeMostPopular(const dictionaryOfNames& diction, std::istream& in, std::ostream& out);
  void findWord(const dictionaryOfNames& dict, std::istream& in, std::ostream& out);
  void deleteWord(dictionaryOfNames& dict, std::istream& in, std::ostream& out);
  void print(const dictionary& dict, std::ostream& out);
  void printWordToSpecificLetter(const dictionaryOfNames& dict, std::istream& in, std::ostream& out);
  void printDictionary(const dictionaryOfNames& dict, std::istream& in, std::ostream& out);
  void maxCountLetterDictionary(const dictionaryOfNames& dict, std::istream& in, std::ostream& out);
  void minCountLetterDictionary(const dictionaryOfNames& dict, std::istream& in, std::ostream& out);
  std::map< char, size_t > countOfLetters(const dictionary& dict);
  void mergeDictionary(dictionaryOfNames& dict, std::istream& in);
  void uniqueWord(dictionaryOfNames& dict, std::istream& in);
  void countIndentical(const dictionaryOfNames& dict, std::istream& in, std::ostream& out);
  void wordsWithLetter(const dictionaryOfNames& dict, std::istream& in, std::ostream& out);
}


#endif
