#include "HelpFunction.h"
#include <algorithm>
#include <string>
namespace timofeev
{
  void splitter(std::string translation, std::string word, vector line, dict_t& dict)
  {
    size_t start;
    size_t end = 0;
    while ((start = translation.find_first_not_of(' ', end)) != std::string::npos)
    {
      end = translation.find(' ', start);
      line.push_back(translation.substr(start, end - start));
    }
    dict[word] = line;
  }

  void addInDict(std::istream& in, std::ostream& out, dict_t& dict)
  {
    std::string word = "";
    std::vector < std::string > line;
    std::string translation;
    in >> word;
    std::getline(in, translation);
    if (dict.count(word) > 0)
    {
      std::string answ = "";
      out << "Word already in dictionary!! Want to rewrite it?" << "\n";
      out << "Yes or No? ";
      in >> answ;

      if (answ == "No")
      {
        return;
      }
      else if (answ != "Yes")
      {
        throw std::logic_error("Invalid");
      }
      line.clear();
    }
    splitter(translation, word, line, dict);
  }

  void printInvalid(std::ostream &out)
  {
    out << "<INVALID COMMAND>";
  }

  void delTrans(std::istream& in, std::ostream& out, dict_t& dict)
  {
    while (true)
    {
      std::string word = "";
      std::string rTrans;
      out << "Write a word (or 'exit'): ";
      in >> word;
      if (word == "exit")
      {
        break;
      }
      out << "Write a translation (or 'exit'): ";
      in >> rTrans;
      if (word == "exit")
      {
        break;
      }
      auto it = dict.find(word);
      if (it != dict.end())
      {
        std::vector < std::string > &lTrans = it->second;
        lTrans.erase(std::remove(lTrans.begin(), lTrans.end(), rTrans), lTrans.end());
        if (lTrans.empty())
        {
          dict.erase(it);
        }
      }
    }
  }

  void printList(const std::vector< std::string > &list, std::ostream &out)
  {
    out << '-' << " ";
    bool flag = false;
    for (const std::string &translation: list)
    {
      if (!flag)
      {
        out << translation;
        flag = true;
      }
      else
      {
        out << " " << translation;
      }
    }
  }

  void printDict(std::ostream &out, dict_t &dict)
  {
    for (const auto &word: dict)
    {
      out << word.first << ' ';
      printList(word.second, out);
      out << '\n';
    }
  }

  void delList(std::vector< std::string > &list)
  {
    std::vector < std::string > tmp;
    for (size_t i = 0; i != list.size(); i++)
    {
      std::string word = list[i];
      tmp.push_back(word);
    }
    for (const std::string &word: tmp)
    {
      list.erase(std::remove(list.begin(), list.end(), word), list.end());
    }
  }

  void delDict(dict_t &dict)
  {
    if (dict.empty())
    {
      throw std::out_of_range("Dictionary empty");
    }
    std::vector < std::string > words;
    for (auto it = dict.begin(); it != dict.end(); it++)
    {
      delList(it->second);
      if (it->second.empty())
      {
        words.push_back(it->first);
      }
    }
    for (const std::string &wordToRemove: words)
    {
      dict.erase(wordToRemove);
    }
  }

  void findTrans(std::ostream& out, const std::string& word, dict_t& dict)
  {
    bool flag = false;
    for (const auto &i: dict)
    {
      if (i.first == word)
      {
        out << i.first << " ";
        printList(i.second, out);
        out << '\n';
        flag = true;
      }
    }
    if (!flag)
    {
      out << "no word matches";
    }
  }
  bool findWord(const std::string& word, dict_t& dict)
  {
    for (const auto &i: dict)
    {
      for (const std::string &translation: i.second)
      {
        if (i.first == word)
        {
          return true;
        }
        else if (translation == word)
        {
          return true;
        }
      }
    }
    return false;
  }
}
