#include "help_commands.h"
#include <stdexcept>

namespace skarlygina
{
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
}