#include "HelpFunction.h"
namespace timofeev
{
  void readDict(std::istream &in, dict_t &dict)
  {
    while(true)
    {
      std::string word = "";
      std::vector< std::string > line;
      std::string translation;
      std::cout << "Write a word (or 'exit'): ";
      in >> word;
      if (dict.count(word) > 0)
      {
        std::cout << "Word already in dictionary!! Want to rewrite it?\n";
        std::cout << "Yes or No?";
        std::string answ = "";
        in >> answ;
        if (answ == "No")
        {
          break;
        }
        else if (answ == "Yes")
        {
          std::cout << "new translation (or 'done' to finish): ";
          while (true) {
            in >> translation;
            if (translation == "done") {
              break;
            }
            line.push_back(translation);
          }
          dict[word] = line;
          continue;
        }
      }
      if (word == "exit") {
        break;
      }
      std::cout << "translation (or 'done' to finish): ";
      while (true) {
        in >> translation;
        if (translation == "done") {
          break;
        }
        line.push_back(translation);
      }
      dict[word] = line;
    }
  }
}