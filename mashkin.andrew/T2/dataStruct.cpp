#include "dataStruct.h"
#include <cmath>
#include <ios>
#include <iostream>
#include <string>

void getKey1(std::istream& inp, std::string& var, mashkin::DataStruct& varData);

/*void getKey2(std::istream& inp, std::string& var, mashkin::DataStruct& varData);
void getKey3(std::istream& inp, std::string& var, mashkin::DataStruct& varData);*/

void getKey1(std::istream& inp, std::string& var, mashkin::DataStruct& varData)
{
  inp >> var;
  std::string doubleSCI;
  std::copy(std::begin(var), std::begin(var) + var.find_first_of(':'), std::back_inserter(doubleSCI));
  var.erase(std::begin(var), std::begin(var) + var.find_first_of(':'));
  if (doubleSCI.find_first_of("eE") != std::string::npos)
  {
    if (doubleSCI.find_first_of('.') == 1 && *std::begin(doubleSCI) != '0')
    {
      varData.key1 = std::stod(doubleSCI);
      std::cout << varData.key1;
    }
  }
  else
  {
    std::cout << "False\n";
  }
}

namespace mashkin
{
  std::istream& operator>>(std::istream& inp, DataStruct& data)
  {
    std::string var;
    DataStruct varData{0.0, 0, ""};
    inp >> var;
    if (*std::begin(var) == '(' && *(std::begin(var) + 1) == ':')
    {
      var.erase(std::begin(var), std::begin(var) + 2);
      if (var == "key1")
      {
        getKey1(inp, var, varData);
      }
      /*else if (var == "key2")
      {
        getKey2(inp, var, varData);
      }
      else if (var == "key3")
      {
        getKey3(inp, var, varData);
      }*/
      else
      {
        inp.setstate(std::ios::failbit);
        return inp;
      }
    }
    else
    {
      inp.setstate(std::ios::failbit);
      return inp;
    }
    return inp;
  }
}
