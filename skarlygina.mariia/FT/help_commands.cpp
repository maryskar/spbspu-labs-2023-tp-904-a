#include "help_commands.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "error_messages.h"
#include "iofmtguard.h"

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

  std::ostream& doPrint(const Dict_t& dict, std::ostream& out)
  {
    using ostreamIterator_t = typename std::ostream_iterator< size_t >;
    if (dict.empty())
    {
      skarlygina::errorEmptyMessage(out);
      std::cout << "\n";
    }
    skarlygina::IofmtGuard guard(out);
    for (auto i = dict.cbegin(); i != dict.cend(); i++)
    {
      out << i->first << " ";
      std::copy(i->second.cbegin(), i->second.cend(), ostreamIterator_t(out, " "));
      i != --dict.cend() ? out << "\n" : out << "\n";
    }
    return out;
  }

  void doWriteInFile(const Dict_t& dict, const std::string& out_name)
  {
    std::ofstream out(out_name);
    skarlygina::doPrint(dict, out);
    out.close();
  }

  Dict_t doIntersect(const std::string dict_name_first, const std::string dict_name_second, Dicts_t& dicts)
  {
    auto iter1 = dicts.find(dict_name_first);
    auto iter2 = dicts.find(dict_name_second);
    Dict_t result;
    for (auto i = iter1->second.cbegin(); i != iter1->second.cend(); i++)
    {
      auto key1 = i->first;
      for (auto j = iter2->second.cbegin(); j != iter2->second.cend(); j++)
      {
        auto key2 = j->first;
        if ((key1 == key2) && (result.find(key1) == result.end()))
        {
          result.emplace(i->first, i->second);
        }
      }
    }
    return (result);
  }

  Dict_t doComplement(const std::string dict_name_first, const std::string dict_name_second, Dicts_t& dicts)
  {
    auto iter1 = dicts.find(dict_name_first);
    auto iter2 = dicts.find(dict_name_second);
    Dict_t result = iter1->second;
    for (auto i = iter2->second.cbegin(); i != iter2->second.cend(); i++)
    {
      auto key = i->first;
      if (result.find(key) != result.end())
      {
        result.erase(key);
      }
    }
    return (result);
  }
}
