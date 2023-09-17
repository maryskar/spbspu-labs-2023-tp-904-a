#ifndef FT_COMMANDS_HPP
#define FT_COMMANDS_HPP
#include <algorithm>
#include <fstream>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "dictionary.hpp"

void createSet(dictionaryOfNames& diction, std::istream& in);
void threeMostPopular(const dictionaryOfNames& diction, std::istream& in, std::ostream& out);
void print(const std::vector< std::pair <std::string, size_t> >& dict, std::ostream& out);
void findWord(const dictionaryOfNames& dict, std::istream& in, std::ostream& out);
void deleteWord(dictionaryOfNames& dict, std::istream& in, std::ostream& out);
//void printWordToSpecificLetter(const dictionaryOfNames& dict, std::istream& in, std::ostream& out);
//void printDictionary(const dictionaryOfNames& dict, std::ostream& out);
//void maxCountLetterDictionary(const dictionaryOfNames& dict, std::ostream& out);
//void minCountLetterDictionary(const dictionaryOfNames& dict, std::ostream& out);
//std::map<char, size_t> countOfLetters(const dictionaryOfNames& dict);
//void mergeDictionary(dictionaryOfNames& dictOfResult, const dictionaryOfNames& dict1, const dictionaryOfNames& dict2);
//void uniqueWord(dictionaryOfNames& dictOfResult, const dictionaryOfNames& dict1, const dictionaryOfNames& dict2);
//void countIndentical(const dictionaryOfNames& dict1, const dictionaryOfNames& dict2, std::ostream& out);
//void wordsWithLetter(const dictionaryOfNames& dict, std::istream& in, std::ostream& out);

#endif