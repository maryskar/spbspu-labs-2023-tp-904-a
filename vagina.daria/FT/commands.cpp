#include "commands.hpp"

void createSet(dictionary& dict, std::istream& in)
{
  std::string filename = "";
  in >> filename;
  std::ifstream file(filename);
  std::string word;

  while (file >> word) 
  {
    word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
    std::transform(word.begin(), word.end(), word.begin(), tolower);
    dict.insert(word);
  }
}
void threeMostPopular(const dictionary& dict, std::ostream& out)
{
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
void findWord(const dictionary& dict, std::istream& in, std::ostream& out)
{
  std::string word = "";
  in >> word;
  try
  {
    auto it = dict.dict_.find(word);
    if (it != dict.dict_.end())
    {
      out << "This word occurs - " << it->second << " times";
    }
    else
    {
      out << "This word is missing";
    }
  }
  catch (const std::out_of_range& )
  {}
}
void deleteWord(dictionary& dict, std::istream& in, std::ostream& out)
{
  std::string word = "";
  in >> word;
  try
  {
    auto it = dict.dict_.find(word);
    if (it != dict.dict_.end())
    {
      dict.dict_.erase(word);
      out << "The word is deleted";
    }
    else
    {
      out << "Error: This word is missing";
    }
  }
  catch (const std::out_of_range& )
  {}
}
void printWordToSpecificLetter(const dictionary& dict, std::istream& in, std::ostream& out)
{
  char letter = ' ';
  in >> letter;
  for (auto it = dict.dict_.begin(); it != dict.dict_.end(); ++it)
  {
    if (it->first[0] == letter) 
    {
      out << it->first << " : " << it->second << std::endl;
    }
  }
}

void printDictionary(const dictionary& dict, std::ostream& out)
{
  std::vector< std::pair <std::string, size_t> > sorted_word_count(dict.dict_.begin(), dict.dict_.end());
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
void maxCountLetterDictionary(const dictionary& dict, std::ostream& out)
{
  std::map<char, size_t> letterFreq;
  letterFreq = countOfLetters(dict);
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
  out << "The most common letter is " << mostFrequentLetter;
}
void minCountLetterDictionary(const dictionary& dict, std::ostream& out)
{
  std::map<char, size_t> letterFreq;
  letterFreq = countOfLetters(dict);
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
  out << "The rarest letter is " << leastFrequentLetter;
}
void mergeDictionary(dictionary& dictOfResult, const dictionary& dict1, const dictionary& dict2)
{
  dictOfResult = dict1;
  for (const auto& pair : dict2.dict_) 
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
}
void uniqueWord(dictionary& dictOfResult, const dictionary& dict1, const dictionary& dict2)
{
  dictOfResult = dict1;
  for (const auto& pair : dict2.dict_)
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
}
void countIndentical(const dictionary& dict1, const dictionary& dict2, std::ostream& out)
{
  for (const auto& pair1 : dict1.dict_) 
  {
    const std::string& word = pair1.first;
    auto it = dict2.dict_.find(word);
    if (it != dict2.dict_.end()) 
    {
      out << word << ": " << pair1.second << " " << it->second << "\n";
    }
  }
}
void wordsWithLetter(const dictionary& dict, std::istream& in, std::ostream& out)
{
  char letter = ' ';
  size_t minCount = 0;
  in >> minCount >> letter;
  for (const auto& pair : dict.dict_)
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
