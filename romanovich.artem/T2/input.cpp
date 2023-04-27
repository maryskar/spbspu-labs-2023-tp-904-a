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
  for (int i = 0; i < list->size(); ++i)
  {
    if (key == list[0])
    {
      unsigned long long firstEl = std::stoi(value, nullptr, 8);
      tuple = {firstEl, std::get<1>(tuple), std::get<2>(tuple)};
    }
    /*if (key == list[1])
    {
      std::string newValue = tryRemoveBrackets(value);
      std::string numerator = std::get<0>(getKeyValue(newValue, " "));
      std::string denominator = std::get<1>(getKeyValue(newValue, " "));
      //unsigned long long secondEl = std::stoi(value, nullptr, 8);
    }
    if (key == list[2])
    {
      std::string thirdEl = value;
    }*/
  }
  return tuple;
}
void
extrudeTupleElemsFromString(std::string &string, int intBegin, int &intEnd, const std::string &divKV,
                            const std::string *list, return_tuple &tuple, const std::string &divEl)
{
  string = string.substr(intBegin, intEnd - intBegin);
  std::string key = std::get<0>(getKeyValue(string, divKV));
  std::string value = std::get<1>(getKeyValue(string, divKV));
  fillTuple(list, key, value, tuple);
  intBegin = intEnd + 1;
  intEnd = static_cast<int>(string.find(divEl, intBegin));
  //std::cout << "key: " << key << std::endl;
  //std::cout << "value: " << value << std::endl;
  //std::cout << "tuple: " << std::get<0>(tuple) << std::endl;
}
return_tuple parseLine(const std::string &str, const std::string &divEl, const std::string &divKV, std::string list[3])
{
  std::string string = str;
  return_tuple tuple;
  int intBegin = 0;
  int intEnd = static_cast<int>(string.find(divEl));
  while (true)
  {
    extrudeTupleElemsFromString(string, intBegin, intEnd, divKV, list, tuple, divEl);
    if (intEnd == -1)
    {
      break;
    }
  }
  return {0, std::make_pair(0, 0), ""};
}
std::string tryRemoveBrackets(const std::string &str)
{
  if (str.size() < 4)
  {
    return str;
  }
  return str.substr(2, str.size() - 4);
}