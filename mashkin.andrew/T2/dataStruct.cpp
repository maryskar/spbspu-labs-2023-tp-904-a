#include "dataStruct.h"
#include <bitset>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

void getKey1(std::istream& inp, std::string& var, mashkin::DataStruct& varData);
void getKey2(std::istream& inp, std::string& var, mashkin::DataStruct& varData);
void getKey3(std::istream& inp, std::string& var, mashkin::DataStruct& varData);

std::string getDoubleString(const mashkin::DataStruct& data)
{
  std::string varString = std::to_string(data.key1);
  size_t varPow = varString.find_first_not_of("0.");
  double dblWithMantissa = 0.0;
  std::string result;
  if (varPow > 1)
  {
    dblWithMantissa = data.key1 * pow(10, varPow - 1);
    result = std::to_string(dblWithMantissa) + "e-" + std::to_string(varPow - 1);
  }
  else
  {
    varPow = varString.find_first_of(".");
    dblWithMantissa = data.key1 / pow(10, (varPow - 1));
    result = std::to_string(dblWithMantissa) + "e+" + std::to_string(varPow - 1);
  }
  while (result.find_last_of('e') - 1 == result.find_last_of('0') &&
         result.find_last_of('0') != std::to_string(dblWithMantissa).find_last_not_of('0') + 1)
  {
    result.erase(std::begin(result) + result.find_last_of('0'));
  }
  {
    return result;
  }
}

std::string getUllBinStr(const mashkin::DataStruct& data)
{
  unsigned long long varUll = data.key2;
  std::string result = "";
  while (varUll)
  {
    result = std::to_string(varUll % 2) + result;
    varUll /= 2;
  }
  result = "0b0" + result;
  return result;
}

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
  std::string::iterator beginIt = std::begin(var) + var.find_first_of('\"');
  std::string::iterator endIt = std::begin(var) + var.find_last_of('\"');
  while (beginIt == endIt)
  {
    std::string varString;
    inp >> varString;
    var += " " + varString;
    endIt = std::begin(var) + var.find_last_of('\"');
  }
  beginIt++;
  std::copy(beginIt, endIt, std::back_inserter(varData.key3));
  var.erase(std::begin(var), endIt + 2);
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

  /*bool comp(const DataStruct& first, const DataStruct& second)
  {
    return first.key1 < second.key1;
  }*/

  std::ostream& operator<<(std::ostream& out, const DataStruct& data)
  {
    out << "(:key1 " << getDoubleString(data);
    out << ":key2 " << getUllBinStr(data);
    out << ":key3 \"" << data.key3 << "\":)";
    return out;
  }
}
