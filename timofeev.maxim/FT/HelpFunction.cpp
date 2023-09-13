#include "HelpFunction.h"
#include <algorithm>
namespace timofeev
{
  void readDict(std::istream &in, dict_t &dict)
  {

    while (true)
    {
      std::string word = "";
      std::vector <std::string> line;
      std::string translation;
      std::cout << "Write a word (or 'exit'): ";
      in >> word;
      if (word == "exit")
      {
        break;
      }
      if (dict.count(word) > 0)
      {
        std::cout << "Word already in dictionary!! Want to rewrite it?\n";
        std::cout << "Yes or No?";
        std::string answ = "";
        in >> answ;
        if (answ == "No")
        {
          continue;
        } else if (answ == "Yes")
        {
          std::cout << "new translation (or 'done' to finish): ";
        }
      }
      else
      {
        std::cout << "translation (or 'done' to finish): ";
        while (true)
        {
          in >> translation;
          if (translation == "done")
          {
            break;
          }
          line.push_back(translation);
        }
        dict[word] = line;
      }
    }
  }

  std::ostream &printInvalid(std::ostream &out)
  {
    out << "<INVALID COMMAND>" << "\n";
  }

  void delTrans(std::istream &in, dict_t &dict)
  {
    while (true)
    {
      std::string word = "";
      std::string rTrans;
      std::cout << "Write a word (or 'exit'): ";
      in >> word;
      if (word == "exit")
      {
        break;
      }
      std::cout << "Write translation to remove: ";
      in >> rTrans;
      auto it = dict.find(word);
      if (it != dict.end())
      {
        std::vector <std::string> &lTrans = it->second;
        lTrans.erase(std::remove(lTrans.begin(), lTrans.end(), rTrans), lTrans.end());
        if (lTrans.empty())
        {
          dict.erase(it);
        }
      }
    }
  }

  void printList(const std::vector <std::string> &list, std::ostream &out)
  {
    out << '-';
    for (const std::string &translation: list)
    {
      out << " " << translation;
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

  void delList(std::vector < std::string > &list)
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

}