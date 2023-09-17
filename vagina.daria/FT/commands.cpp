#include "commands.hpp"
#include <algorithm>
#include <fstream>

void createSet(dictionaryOfNames& diction, std::istream& in)
{
  std::string filename = "";
  in >> filename;
  std::ifstream file(filename);
  std::string word;
  std::string name = "";
  in >> name;
  dictionary dict;
  while (file >> word) 
  {
    word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
    std::transform(word.begin(), word.end(), word.begin(), tolower);
    dict.insert(word);
  }
  diction.insert({ name, dict });
}
void threeMostPopular(const dictionaryOfNames& diction, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  dictionary dict = findSpecificDict(diction, name);
  std::vector< std::pair <std::string, size_t> > sorted_word_count(dict.dict_.begin(), dict.dict_.end());
  std::sort(sorted_word_count.begin(), sorted_word_count.end(), [](const auto& p1, const auto& p2) { return p1.second > p2.second; });
  std::vector< std::pair <std::string, size_t> > first_three_keys;
  std::copy_n(sorted_word_count.begin(), 3, std::back_inserter(first_three_keys));
  print(first_three_keys, out);
}
void print(const std::vector< std::pair <std::string, size_t> >& dict, std::ostream& out)
{
  for (const auto& pair : dict) 
  {
    out << pair.first << ": " << pair.second << '\n';
  }
}
void findWord(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string word = "";
  std::string name = "";
  in >> name >> word;
  dictionary diction = findSpecificDict(dict, name);
  try
  {
    auto it = diction.dict_.find(word);
    if (it != diction.dict_.end())
    {
      out << "This word occurs - " << it->second << " times" << "\n";
    }
    else
    {
      out << "This word is missing" << "\n";
    }
  }
  catch (const std::out_of_range& )
  {}
}
void deleteWord(dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string word = "";
  std::string name = "";
  in >> name >> word;
  dictionary diction = findSpecificDict(dict, name);
  try
  {
    auto it = diction.dict_.find(word);
    if (it != diction.dict_.end())
    {
      diction.dict_.erase(word);
      out << "The word is deleted" << "\n";
      dict.erase(name);
      dict.insert({name, diction});
    }
    else
    {
      out << "Error: This word is missing" << "\n";
    }
  }
  catch (const std::out_of_range& )
  {}
}
void printWordToSpecificLetter(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  char letter = ' ';
  std::string name = "";
  in >> name >> letter;
  dictionary diction = findSpecificDict(dict, name);
  for (auto it = diction.dict_.begin(); it != diction.dict_.end(); ++it)
  {
    if (it->first[0] == letter) 
    {
      out << it->first << " : " << it->second << "\n";
    }
  }
}
void printDictionary(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  dictionary diction = findSpecificDict(dict, name);
  std::vector< std::pair <std::string, size_t> > sorted_word_count(diction.dict_.begin(), diction.dict_.end());
  std::sort(sorted_word_count.begin(), sorted_word_count.end(), [](const auto& p1, const auto& p2) { return p1.second > p2.second; });
  print(sorted_word_count, out);
}
std::map<char, size_t> countOfLetters(const dictionary& dict)
{
  std::map<char, size_t> letterFreq;
  for (auto& word : dict.dict_)
  {
    for (char letter : word.first) {
      if (letterFreq.find(letter) != letterFreq.end())
      {
        letterFreq[letter]++;
      }
      else
      {
        letterFreq[letter] = 1;
      }
    }
  }
  return letterFreq;
}
void maxCountLetterDictionary(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  dictionary diction = findSpecificDict(dict, name);
  std::map<char, size_t> letterFreq;
  letterFreq = countOfLetters(diction);
  char mostFrequentLetter = ' ';
  size_t maxFreq = 0;
  for (auto& letter : letterFreq) 
  {
    if (letter.second > maxFreq) 
    {
      maxFreq = letter.second;
      mostFrequentLetter = letter.first;
    }
  }
  out << "The most common letter is " << mostFrequentLetter << "\n";
}
void minCountLetterDictionary(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  dictionary diction = findSpecificDict(dict, name);
  std::map<char, size_t> letterFreq;
  letterFreq = countOfLetters(diction);
  char leastFrequentLetter = ' ';
  size_t minFreq = std::numeric_limits<size_t>::max();
  for (auto& letter : letterFreq)
  {
    if (letter.second < minFreq)
    {
      minFreq = letter.second;
      leastFrequentLetter = letter.first;
    }
  }
  out << "The rarest letter is " << leastFrequentLetter << "\n";
}
void mergeDictionary(dictionaryOfNames& dict, std::istream& in)
{
  std::string nameFirst = "";
  std::string nameSecond = "";
  in >> nameFirst >> nameSecond;
  dictionary diction1 = findSpecificDict(dict, nameFirst);
  dictionary diction2 = findSpecificDict(dict, nameSecond);
  dictionary dictOfResult = diction1;
  for (const auto& pair : diction2.dict_)
  {
    if (dictOfResult.dict_.find(pair.first) != dictOfResult.dict_.end()) 
    {
      dictOfResult.dict_[pair.first] += pair.second;
    }
    else 
    {
      dictOfResult.dict_[pair.first] = pair.second;
    }
  }
  std::string name = "";
  in >> name;
  dict.insert({ name, dictOfResult });
}
void uniqueWord(dictionaryOfNames& dict, std::istream& in)
{
  std::string nameFirst = "";
  std::string nameSecond = "";
  in >> nameFirst >> nameSecond;
  dictionary diction1 = findSpecificDict(dict, nameFirst);
  dictionary diction2 = findSpecificDict(dict, nameSecond);
  dictionary dictOfResult = diction1;
  for (const auto& pair : diction2.dict_)
  {
    if (dictOfResult.dict_.find(pair.first) == dictOfResult.dict_.end())
    {
      dictOfResult.dict_[pair.first] = pair.second;
    }
    else
    {
      dictOfResult.dict_.erase(pair.first);
    }
  }
  std::string name = "";
  in >> name;
  dict.insert({ name, dictOfResult });
}
void countIndentical(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string nameFirst = "";
  std::string nameSecond = "";
  in >> nameFirst >> nameSecond;
  dictionary diction1 = findSpecificDict(dict, nameFirst);
  dictionary diction2 = findSpecificDict(dict, nameSecond);
  for (const auto& pair1 : diction1.dict_)
  {
    const std::string& word = pair1.first;
    auto it = diction2.dict_.find(word);
    if (it != diction2.dict_.end())
    {
      out << word << ": " << pair1.second << " " << it->second << "\n";
    }
  }
}
void wordsWithLetter(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  dictionary diction = findSpecificDict(dict, name);
  char letter = ' ';
  size_t minCount = 0;
  in >> minCount >> letter;
  for (const auto& pair : diction.dict_)
  {
    const std::string& word = pair.first;
    int count = 0;
    for (char c : word) 
    {
      if (c == letter) 
      {
        count++;
        if (count >= minCount)
        {
          out << word << "\n";
          break;
        }
      }
    }
  }
}
