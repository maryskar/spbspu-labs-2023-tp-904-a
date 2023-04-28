#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include "datastruct.h"
#include "input.h"
using return_tuple = std::tuple< unsigned long long, std::pair< long long, unsigned long long >, std::string >;
using string_pair = std::tuple< std::string, std::string >;
bool compareK1(const DataStruct &a, const DataStruct &b)
{
  return a.key1 < b.key1;
}
bool compareK2(const DataStruct &a, const DataStruct &b)
{
  return (a.key2.first / a.key2.second) < (b.key2.first / b.key2.second);
}
bool compareK3(const DataStruct &a, const DataStruct &b)
{
  return a.key3.length() < b.key3.length();
}
void print(const DataStruct &dataStruct)
{
  dataStruct.printDS();
}
void safeReplace(std::string &line, const std::string &oldStr, const std::string &newStr)
{
  auto pos = line.find(oldStr);
  while (pos != std::string::npos)
  {
    line = line.replace(pos, oldStr.length(), newStr);
    pos = line.find(oldStr);
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
  std::sort(ds.begin(), ds.end(), compareK3);
  std::sort(ds.begin(), ds.end(), compareK2);
  std::sort(ds.begin(), ds.end(), compareK1);
  std::for_each(ds.begin(), ds.end(), print);
  return 0;
}
