#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include "datastruct.h"
#include "input.h"
using string_pair = std::tuple< std::string, std::string >;
void safeReplace(std::string &line, const std::string &oldStr, const std::string &newStr)
{
  long unsigned int pos = static_cast<long unsigned int>(line.find(oldStr));
  while (pos != std::string::npos)
  {
    line = line.replace(pos, oldStr.length(), newStr);
    pos = static_cast<int>(line.find(oldStr));
  }
}
int main()
{
  std::vector< DataStruct > ds;
  for (std::string line; std::getline(std::cin, line);)
  {
    safeReplace(line, ":D", ";D");
    safeReplace(line, ":)", ")");
    safeReplace(line, "(:", "(");
    line = tryRemoveBrackets(line);
    std::string keyNames[3] = {"key1", "key2", "key3"};
    try
    {
      return_tuple tuple = parseLine(line, ":", " ", keyNames);
      ds.emplace_back(tuple);
    }
    catch (...)
    {
    }
  }
  std::sort(ds.begin(), ds.end(), DataStruct::compareK3);
  std::sort(ds.begin(), ds.end(), DataStruct::compareK2);
  std::sort(ds.begin(), ds.end(), DataStruct::compareK1);
  std::for_each(ds.begin(), ds.end(), DataStruct::print);
  return 0;
}
