#include "dataStruct.h"
#include <bitset>
#include <cstddef>
#include <ios>
#include <iostream>
#include <string>

void getKey1(std::istream& inp, std::string& var, mashkin::DataStruct& varData);
void getKey2(std::istream& inp, std::string& var, mashkin::DataStruct& varData);
void getKey3(std::istream& inp, std::string& var, mashkin::DataStruct& varData);

void getKey1(std::istream& inp, std::string& var, mashkin::DataStruct& varData)
{
  inp >> var;
  std::string dblSCI;
  std::copy(std::begin(var), std::begin(var) + var.find_last_of(':'), std::back_inserter(dblSCI));
  var.erase(std::begin(var), std::begin(var) + var.find_last_of(':') + 1);
  if (dblSCI.find_first_of("eE") != std::string::npos && dblSCI.find_first_of('.') == 1 && *dblSCI.begin() != '0')
  {
    varData.key1 = std::stod(dblSCI);
  }
  else
  {
    inp.setstate(std::ios::failbit);
  }
}

void getKey2(std::istream& inp, std::string& var, mashkin::DataStruct& varData)
{
  inp >> var;
  if (var.find_first_of("Bb") != 1)
  {
    inp.setstate(std::ios::failbit);
    return;
  }
  else
  {
    std::string binaryUll;
    var.erase(std::begin(var), std::begin(var) + 2);
    std::copy(std::begin(var), std::begin(var) + var.find_last_of(':'), std::back_inserter(binaryUll));
    varData.key2 = std::bitset< 64 >(binaryUll).to_ullong();
    var.erase(std::begin(var), std::begin(var) + var.find_last_of(':') + 1);
  }
}

void getKey3(std::istream& inp, std::string& var, mashkin::DataStruct& varData)
{
  inp >> var;
  if (var.find_first_of('\"') == std::string::npos)
  {
    inp.setstate(std::ios::failbit);
    return;
  }
  std::string::iterator beginIt = std::begin(var) + var.find_first_of('\"') + 1;
  std::string::iterator endIt = std::begin(var) + var.find_last_of('\"');
  std::copy(beginIt, endIt, std::back_inserter(varData.key3));
}

namespace mashkin
{
  std::istream& operator>>(std::istream& inp, DataStruct& data)
  {
    std::string var;
    DataStruct varData{0.0, 0, ""};
    inp >> var;
    if (*std::begin(var) != '(' || *(std::begin(var) + 1) != ':')
    {
      inp.setstate(std::ios::failbit);
      return inp;
    }
    var.erase(std::begin(var), std::begin(var) + 2);
    for (size_t i = 0; i < 3; ++i)
    {
      if (var == "key1")
      {
        getKey1(inp, var, varData);
      }
      else if (var == "key2")
      {
        getKey2(inp, var, varData);
      }
      else if (var == "key3")
      {
        getKey3(inp, var, varData);
      }
      else
      {
        inp.setstate(std::ios::failbit);
        return inp;
      }
    }
    if (inp.fail())
    {
      return inp;
    }
    data = varData;
    return inp;
  }
  std::ostream& operator<<(std::ostream& out, DataStruct& data)
  {
    out << "(:key1 " << std::scientific << data.key1;
    out << ":key2 0b" << std::bitset< 64 >(data.key2);
    out << ":key3 \"" << data.key3 << "\":)\n";
    return out;
  }
}
