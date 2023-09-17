#ifndef FT_COMMANDS_HPP
#define FT_COMMANDS_HPP
#include <algorithm>
#include <fstream>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "dictionary.hpp"

void createSet(dictionary& dict, std::istream& in);
void threeMostPopular(const dictionary& dict, std::ostream& out);
void print(const std::vector< std::pair <std::string, size_t> >& dict, std::ostream& out);
void findWord(const dictionary& dict, std::istream& in, std::ostream& out);
void deleteWord(dictionary& dict, std::istream& in, std::ostream& out);
void printWordToSpecificLetter(const dictionary& dict, std::istream& in, std::ostream& out);
void printDictionary(const dictionary& dict, std::ostream& out);
void maxCountLetterDictionary(const dictionary& dict, std::ostream& out);
void minCountLetterDictionary(const dictionary& dict, std::ostream& out);
std::map<char, size_t> countOfLetters(const dictionary& dict);
void mergeDictionary(dictionary& dictOfResult, const dictionary& dict1, const dictionary& dict2);
void uniqueWord(dictionary& dictOfResult, const dictionary& dict1, const dictionary& dict2);
void countIndentical(const dictionary& dict1, const dictionary& dict2, std::ostream& out);
void wordsWithLetter(const dictionary& dict, std::istream& in, std::ostream& out);

#endif