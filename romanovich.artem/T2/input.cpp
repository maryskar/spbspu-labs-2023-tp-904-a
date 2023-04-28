#include "input.h"
#include <string>
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
      //std::stoi(value, nullptr, 8)
      unsigned long long val = std::stoi(value, nullptr, 10);
      tuple = {val, std::get< 1 >(tuple), std::get< 2 >(tuple)};
    }
    if (key == list[1])
    {
      std::string newValue = tryRemoveBrackets(value);
      long long numerator = std::stoi(std::get< 1 >(getKeyValue(std::get< 0 >(getKeyValue(newValue, ";")), " ")));
      unsigned long long denominator = std::stoi(
        std::get< 1 >(getKeyValue(std::get< 1 >(getKeyValue(newValue, ";")), " ")));
      tuple = {std::get< 0 >(tuple), std::make_pair(numerator, denominator), std::get< 2 >(tuple)};
    }
    if (key == list[2])
    {
      tuple = {std::get< 0 >(tuple), std::get< 1 >(tuple), value};
    }
  }
  return tuple;
}
void
extrudeTupleElemsFromString(const std::string &str, int &begin, int &end, const std::string &divKV,
                            const std::string *list, return_tuple &tuple, const std::string &divEl)
{
  std::string string = str.substr(begin, end - begin);
//  std::cout << "string: " << string << std::endl;
  auto subBegin = begin;
  auto subeEnd = end;
  if (/*(string.find('\"') != std::string::npos) && */static_cast<int>(string.find('\"')) != -1)
  {
    begin = end + 1;
    end = static_cast<int>(str.find(divEl, begin));
    std::string leftoverString = str.substr(begin - 1, end - begin);
    string += leftoverString;
    begin = subBegin;
    end = subeEnd;
  }
  std::string key = std::get< 0 >(getKeyValue(string, divKV));
  std::string value = std::get< 1 >(getKeyValue(string, divKV));
  fillTuple(list, key, value, tuple);
  //std::cout << " key: " << key << std::endl;
  //std::cout << " value: " << value << std::endl;
  //std::cout << "tuple: " << std::get< 0 >(tuple) << " " << std::get< 1 >(tuple).first << " "
  //          << std::get< 1 >(tuple).second << std::get< 2 >(tuple) << " " << std::endl << std::endl;
}
return_tuple
parseLine(const std::string &str, const std::string &divEl, const std::string &divKV, std::string list[3])
{
  const std::string &string = str; //можно убрать
  return_tuple tuple;
  int begin = 0;
  int end = static_cast<int>(string.find(divEl));
  while ((end != std::string::npos) && (end != -1))
  {
    extrudeTupleElemsFromString(string, begin, end, divKV, list, tuple, divEl);
    begin = end + 1;
    end = static_cast<int>(str.find(divEl, begin));
  }
  if (/*(end != std::string::npos) && */(end != -1))
  {
    extrudeTupleElemsFromString(string, begin, end, divKV, list, tuple, divEl);
  }
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
