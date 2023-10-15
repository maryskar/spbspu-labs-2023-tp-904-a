#include "commands.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <set>

void vagina::messageEmptyCommand(std::ostream& out)
{
  out << "<EMPTY>" << '\n';
}
void vagina::createSet(dictionaryOfNames& diction, std::istream& in)
{
  std::string filename = "";
  in >> filename;
  if (filename.empty())
  {
    throw std::invalid_argument("Invalid input: Filename is empty");
  }
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("File didn't open");
  }
  std::string word = "";
  std::string name = "";
  in >> name;
  if (name.empty())
  {
    throw std::invalid_argument("Invalid input: Name is empty");
  }
  dictionary dict;
  while (file)
  {
    file >> word;
    if (!word.empty())
    {
      try
      {
        word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
        std::transform(word.begin(), word.end(), word.begin(), tolower);
        dict.insert(word);
      }
      catch (const std::invalid_argument& e)
      {}
    }
    else
    {
      throw std::invalid_argument("Incorrect word");
    }
  }
  diction.insert({ name, dict });
}
bool vagina::isGreater(const std::pair< std::string, size_t >& p1, const std::pair< std::string, size_t >& p2)
{
  return p1.second > p2.second;
}
void vagina::print(const dictionary& dict, std::ostream& out)
{
  for (const auto& pair : dict.dict_)
  {
    out << pair.first << ": " << pair.second << '\n';
  }
}
void vagina::sortAndPrintFromTheLargest(const dictionary& wordFrequency, std::ostream& out)
{
  std::map< size_t, std::set< std::string >, std::greater < size_t > > sortedWordFrequency;
  for (const auto& pair : wordFrequency.dict_)
  {
    sortedWordFrequency[pair.second].insert(pair.first);
  }
  for (const auto& freqPair : sortedWordFrequency)
  {
    for (const auto& word : freqPair.second)
    {
      out << word << ": " << freqPair.first << '\n';
    }
  }
}
void vagina::threeMostPopular(const dictionaryOfNames& diction, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  if (name.empty())
  {
    throw std::invalid_argument("Invalid input: Name is empty");
  }
  dictionary dict = findSpecificDict(diction, name);
  if (dict.empty())
  {
    throw std::invalid_argument("Dictionary is Empty");
  }
  std::vector< std::pair < std::string, size_t > > sorted_word_count(dict.dict_.begin(), dict.dict_.end());
  if (sorted_word_count.size() < 3)
  {
    throw std::logic_error("Invalid parameter");
  }
  std::sort(sorted_word_count.begin(), sorted_word_count.end(), isGreater);
  dictionary first_three_keys;
  std::copy_n(sorted_word_count.begin(), 3, std::inserter(first_three_keys.dict_, first_three_keys.dict_.begin()));
  sortAndPrintFromTheLargest(first_three_keys, out);
}
void vagina::findWord(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string word = "";
  std::string name = "";
  in >> name >> word;
  if (name.empty() || word.empty())
  {
    throw std::invalid_argument("Invalid input: Name or word is empty");
  }
  dictionary diction = findSpecificDict(dict, name);
  if (diction.empty())
  {
    throw std::invalid_argument("Dictionary is Empty");
  }
  auto it = diction.dict_.find(word);
  if (it != diction.dict_.end())
  {
    out << "This word occurs - " << it->second << " times" << '\n';
  }
  else
  {
    out << "This word is missing" << '\n';
  }
}
void vagina::deleteWord(dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string word = "";
  std::string name = "";
  in >> name >> word;
  if (name.empty() || word.empty())
  {
    throw std::invalid_argument("Invalid input: Name or word is empty");
  }
  dictionary diction = findSpecificDict(dict, name);
  if (diction.empty())
  {
    throw std::invalid_argument("Dictionary is Empty");
  }
  auto it = diction.dict_.find(word);
  if (it != diction.dict_.end())
  {
    diction.dict_.erase(word);
    out << "The word is deleted" << '\n';
    dict.erase(name);
    dict.insert({ name, diction });
  }
  else
  {
    out << "Error: This word is missing" << '\n';
  }
}
bool compareTheFirstLetter(const std::pair< std::string, size_t >& firstLetter, char letter)
{
  return firstLetter.first[0] == letter;
}
void vagina::printWordToSpecificLetter(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  char letter = ' ';
  std::string name = "";
  in >> name >> letter;
  if (name.empty())
  {
    throw std::invalid_argument("Invalid input: Name is empty or invalid letter");
  }
  if (!std::isalpha(letter))
  {
    throw std::logic_error("Input not a letter");
  }
  dictionary diction = findSpecificDict(dict, name);
  if (diction.dict_.empty())
  {
    throw std::invalid_argument("Dictionary is Empty");
  }
  try
  {
    using namespace std::placeholders;
    auto func = std::bind(compareTheFirstLetter, _1, letter);
    dictionary res;
    std::copy_if(diction.dict_.begin(), diction.dict_.end(), std::inserter(res.dict_, res.dict_.begin()), func);
    print(res, out);
  }
  catch (const std::out_of_range& e)
  {}
}
void vagina::printDictionary(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  if (name.empty())
  {
    throw std::invalid_argument("Invalid input: Name is empty");
  }
  dictionary diction = findSpecificDict(dict, name);
  if (diction.empty())
  {
    throw std::invalid_argument("Dictionary is Empty");
  }
  dictionary result = diction;
  sortAndPrintFromTheLargest(result, out);
}
std::map< char, size_t > vagina::countOfLetters(const dictionary& dict)
{
  std::map< char, size_t > letterFreq;
  for (auto& word : dict.dict_)
  {
    for (char letter : word.first)
    {
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
bool isLess(const std::pair< char, size_t >& p1, const std::pair< char, size_t >& p2)
{
  return p1.second < p2.second;
}
void vagina::maxCountLetterDictionary(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  if (name.empty())
  {
    throw std::invalid_argument("Invalid input: Name is empty");
  }
  dictionary diction = findSpecificDict(dict, name);
  if (diction.empty())
  {
    throw std::invalid_argument("Dictionary is Empty");
  }
  std::map< char, size_t > letterFreq;
  letterFreq = countOfLetters(diction);
  using namespace std::placeholders;
  auto func = std::bind(isLess, _1, _2);
  auto maxFreqLetter = std::max_element(letterFreq.begin(), letterFreq.end(), func);
  out << "The most common letter is " << '"' << maxFreqLetter->first << '"' << '\n';
}
void vagina::minCountLetterDictionary(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  if (name.empty())
  {
    throw std::invalid_argument("Invalid input: Name is empty");
  }
  dictionary diction = findSpecificDict(dict, name);
  if (diction.empty())
  {
    throw std::invalid_argument("Dictionary is Empty");
  }
  std::map< char, size_t > letterFreq;
  letterFreq = countOfLetters(diction);
  using namespace std::placeholders;
  auto func = std::bind(isLess, _1, _2);
  auto minFreqLetter = std::min_element(letterFreq.begin(), letterFreq.end());
  out << "The rarest letter is " << '"' << minFreqLetter->first << '"' << '\n';
}
void vagina::mergeDictionary(dictionaryOfNames& dict, std::istream& in)
{
  std::string nameFirst = "";
  std::string nameSecond = "";
  in >> nameFirst >> nameSecond;
  if (nameFirst.empty() || nameSecond.empty())
  {
    throw std::invalid_argument("Invalid input: Name is empty");
  }
  dictionary diction1 = findSpecificDict(dict, nameFirst);
  dictionary diction2 = findSpecificDict(dict, nameSecond);
  if (diction1.empty() || diction2.empty())
  {
    throw std::invalid_argument("Dictionary is Empty");
  }
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
  if (name.empty())
  {
    throw std::invalid_argument("Invalid input: Name is empty");
  }
  dict.insert({ name, dictOfResult });
}
void vagina::uniqueWord(dictionaryOfNames& dict, std::istream& in)
{
  std::string nameFirst = "";
  std::string nameSecond = "";
  in >> nameFirst >> nameSecond;
  if (nameFirst.empty() || nameSecond.empty())
  {
    throw std::invalid_argument("Invalid input: Name is empty");
  }
  dictionary diction1 = findSpecificDict(dict, nameFirst);
  dictionary diction2 = findSpecificDict(dict, nameSecond);
  if (diction1.empty() || diction2.empty())
  {
    throw std::invalid_argument("Dictionary is Empty");
  }
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
  if (name.empty())
  {
    throw std::invalid_argument("Invalid input: Name is empty");
  }
  dict.insert({ name, dictOfResult });
}
void vagina::countIndentical(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string nameFirst = "";
  std::string nameSecond = "";
  in >> nameFirst >> nameSecond;
  if (nameFirst.empty() || nameSecond.empty())
  {
    throw std::invalid_argument("Invalid input: Name is empty");
  }
  dictionary diction1 = findSpecificDict(dict, nameFirst);
  dictionary diction2 = findSpecificDict(dict, nameSecond);
  if (diction1.empty() || diction2.empty())
  {
    throw std::invalid_argument("Dictionary is Empty");
  }
  for (const auto& pair1 : diction1.dict_)
  {
    const std::string& word = pair1.first;
    auto it = diction2.dict_.find(word);
    if (it != diction2.dict_.end())
    {
      out << word << ": " << pair1.second << " " << it->second << '\n';
    }
  }
}
bool isWordMatchingCondition(const std::pair<std::string, size_t>& wordInfo, char letter, size_t minCount)
{
  const std::string& word = wordInfo.first;
  size_t count = std::count(word.begin(), word.end(), letter);
  return (count >= minCount);
}
void vagina::wordsWithLetter(const dictionaryOfNames& dict, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  if (name.empty())
  {
    throw std::invalid_argument("Invalid input: Name is empty");
  }
  dictionary diction = findSpecificDict(dict, name);
  if (diction.empty())
  {
    throw std::invalid_argument("Dictionary is Empty");
  }
  char letter = ' ';
  size_t minCount = 0;
  in >> minCount >> letter;
  if (!std::isalpha(letter) || minCount < 0)
  {
    throw std::logic_error("Input not a letter or not a minCount");
  }
  dictionary matchingWords;
  using namespace std::placeholders;
  auto func = std::bind(isWordMatchingCondition, _1, letter, minCount);
  std::copy_if(diction.dict_.begin(), diction.dict_.end(), std::inserter(matchingWords.dict_, matchingWords.dict_.begin()), func);
  print(matchingWords, out);
}
