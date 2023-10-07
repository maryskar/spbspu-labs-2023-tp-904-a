#include "help_commands.h"
#include <stdexcept>
#include <algorithm>

namespace skarlygina
{
  void redactWord(std::string& str)
  {
    if (std::ispunct(str.back()))
    {
      str.pop_back();
      redactWord(str);
    }
  }

  std::string getWordFromString(std::string& str)
  {
    while (std::isspace(str[0]) && !str.empty())
    {
      str.erase(0, 1);
    }
    if (str.empty())
    {
      throw std::logic_error{"Empty error"};
    }
    auto whitespace = str.find(' ');
    std::string word = "";
    if (whitespace == str.npos)
    {
      word = str;
      str.clear();
      return word;
    }
    word = str.substr(0, whitespace);
    str.erase(0, whitespace + 1);
    return word;
  }

  void makeDictStr(std::string string, size_t str_number, Dict_t& dict)
  {
    std::string word = "";
    while (!string.empty())
    {
      word = getWordFromString(string);
      std::transform(word.begin(), word.end(), word.begin(), std::tolower);
      redactWord(word);
      if (dict.find(word) != dict.end())
      {
        (*dict.find(word)).second.push_back(str_number);
        (*dict.find(word)).second.unique();
      }
      else
      {
        dict.emplace(word, List_t());
        (*dict.find(word)).second.push_back(str_number);
      }
    }
  }
}