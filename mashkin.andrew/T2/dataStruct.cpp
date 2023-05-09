#include "dataStruct.h"
#include <iostream>
#include <string>
#include <ios>

namespace mashkin
{
  std::istream& operator>>(std::istream& inp, DataStruct& data)
  {
    std::string var;
    inp >> var;
    if (var[0] == '(' && var[1] == ':')
    {
      var.erase(std::begin(var), std::begin(var) + 2);
      std::cout << var;
    }
    else
    {
      inp.setstate(std::ios::failbit);
      return inp;
    }
    return inp;
  }
}
