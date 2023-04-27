#include "input.h"
#include <string>
#include <iostream>
string_pair getKeyValue(const std::string &kv, const std::string &divKV)
{
  const std::string &new_kv = kv;
  std::string key = kv.substr(0, static_cast<int>(kv.find(divKV)));
  std::string value = new_kv.substr(static_cast<int>(kv.find(divKV)) + 1, new_kv.size() - 1);
  return {key, value};
}
return_tuple fillTuple(const std::string *list, const std::string &key, const std::string &value, return_tuple &tuple)
{
  for (long unsigned int i = 0; i < list->size(); ++i)
  {
    if (key == list[0])
    {
      tuple = {std::stoi(value, nullptr, 8), std::get<1>(tuple), std::get<2>(tuple)};
    }
    if (key == list[1])
    {
      std::string newValue = tryRemoveBrackets(value);
      //std::cout << "newValue: " << newValue << std::endl;
      long long numerator = std::stoi(std::get<1>(getKeyValue(std::get<0>(getKeyValue(newValue, ";")), " ")));
      unsigned long long denominator = std::stoi(
        std::get<1>(getKeyValue(std::get<1>(getKeyValue(newValue, ";")), " ")));
      //std::cout << "numerator: " << numerator << std::endl;
      //std::cout << "denominator: " << denominator << std::endl;
      tuple = {std::get<0>(tuple), std::make_pair(numerator, denominator), std::get<2>(tuple)};
    }
    if (key == list[2])
    {
      tuple = {std::get<0>(tuple), std::get<1>(tuple), value};
    }
  }
  return tuple;
}
void
extrudeTupleElemsFromString(const std::string &str, int intBegin, int &intEnd, const std::string &divKV,
                            const std::string *list, return_tuple &tuple)
{
  const std::string &string = str.substr(intBegin, intEnd - intBegin);
  //std::cout << "string: " << string << std::endl;
  std::string key = std::get<0>(getKeyValue(string, divKV));
  std::string value = std::get<1>(getKeyValue(string, divKV));
  fillTuple(list, key, value, tuple);
  //std::cout << "key: " << key << std::endl;
  //std::cout << "value: " << value << std::endl;
  //std::cout << "tuple: " << std::get<0>(tuple) << " " << std::get<1>(tuple).first << " " << std::get<1>(tuple).second
  //  << std::get<2>(tuple) << " " << std::endl;
}
return_tuple parseLine(const std::string &str, const std::string &divEl, const std::string &divKV, std::string list[3])
{
  const std::string &string = str;
  return_tuple tuple;
  int intBegin = 0;
  int intEnd = static_cast<int>(string.find(divEl));
  while (intEnd != -1)
  {
    extrudeTupleElemsFromString(string, intBegin, intEnd, divKV, list, tuple);
    intBegin = intEnd + 1;
    intEnd = static_cast<int>(str.find(divEl, intBegin));
  }
  extrudeTupleElemsFromString(string, intBegin, intEnd, divKV, list, tuple);
  return tuple;
}
std::string tryRemoveBrackets(const std::string &str)
{
  if (str.size() < 2)
  {
    return str;
  }
  return str.substr(1, str.size() - 2);
}
