#include "input.h"
#include <string>
#include <algorithm>
using constr = const std::string;
std::string tryRemoveBrackets(constr &str)
{
  if (str.size() < 2)
  {
    return str;
  }
  return str.substr(1, str.size() - 2);
}
void safeReplace(std::string &line, constr &oldStr, constr &newStr)
{
  long unsigned int pos = static_cast<long unsigned int>(line.find(oldStr));
  while (pos != std::string::npos)
  {
    line = line.replace(pos, oldStr.length(), newStr);
    pos = static_cast<int>(line.find(oldStr));
  }
}
string_pair getKeyValue(constr &kv, constr &divKV)
{
  const std::string &new_kv = kv;
  std::string key = kv.substr(0, static_cast<int>(kv.find(divKV)));
  std::string value = new_kv.substr(static_cast<int>(kv.find(divKV)) + 1, new_kv.size() - 1);
  return {key, value};
}
return_tuple fillTuple(constr *list, constr &key, constr &value, return_tuple &tuple)
{
  for (long unsigned int i = 0; i < list->size(); ++i)
  {
    if (key == list[0])
    {
      unsigned long long val = std::stoi(value, nullptr, 10);
      tuple = {val, std::get< 1 >(tuple), std::get< 2 >(tuple)};
    }
    if (key == list[1])
    {
      std::string val = tryRemoveBrackets(value);
      string_pair keyValueNum = getKeyValue(std::get< 0 >(getKeyValue(val, ";")), " ");
      string_pair keyValueDenom = getKeyValue(std::get< 1 >(getKeyValue(val, ";")), " ");
      long long numerator = std::stoi(std::get< 1 >(keyValueNum));
      unsigned long long denominator = std::stoi(std::get< 1 >(keyValueDenom));
      tuple = {std::get< 0 >(tuple), std::make_pair(numerator, denominator), std::get< 2 >(tuple)};
    }
    if (key == list[2])
    {
      tuple = {std::get< 0 >(tuple), std::get< 1 >(tuple), value};
    }
  }
  return tuple;
}
void extrudeTupleElemsFromString(
  constr &str, int &begin, int &end, constr &divKV, constr *list, return_tuple &tuple, constr &divEl, bool &colonCase)
{
  std::string string = str.substr(begin, end - begin);
  int subBegin = begin;
  int subeEnd = end;
  if (static_cast<int>(std::count(string.begin(), string.end(), '\"')) == 1)
  {
    colonCase = true;
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
}
return_tuple parseLine(constr &str, constr &divEl, constr &divKV, std::string list[3])
{
  return_tuple tuple;
  int begin = 0;
  int end = static_cast<int>(str.find(divEl));
  bool afterColonCase = false;
  while (end != -1)
  {
    extrudeTupleElemsFromString(str, begin, end, divKV, list, tuple, divEl, afterColonCase);
    begin = end + 1;
    end = static_cast<int>(str.find(divEl, begin));
  }
  if (afterColonCase)
  {
    if (end != -1)
    {
      extrudeTupleElemsFromString(str, begin, end, divKV, list, tuple, divEl, afterColonCase);
    }
  }
  else
  {
    extrudeTupleElemsFromString(str, begin, end, divKV, list, tuple, divEl, afterColonCase);
  }
  return tuple;
}
