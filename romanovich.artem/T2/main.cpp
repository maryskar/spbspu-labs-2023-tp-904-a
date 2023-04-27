#include <string>
#include <iostream>
#include <tuple> //(:key1 10ull:key2 (:N -1:D 5:):key3 "Data":)
#include <vector>
#include <algorithm>
#include "datastruct.h"
#include "input.h"
using return_tuple = std::tuple<unsigned long long, std::pair<long long, unsigned long long>, std::string>;
using string_pair = std::tuple<std::string, std::string>;
bool compareK1(const DataStruct &a, const DataStruct &b)
{
  return a.key1 > b.key1;
}
void print(const DataStruct &dataStruct)
{
  dataStruct.print();
}
int main()
{
  std::vector<DataStruct> ds;
  for (std::string line; std::getline(std::cin, line);)
  {
    line = line.replace(line.find(":D"), 2, ";D");
    line = line.replace(line.find(":)"), 2, ")");
    line = line.replace(line.find(":)"), 2, ")");
    line = line.replace(line.find("(:"), 2, "(");
    line = line.replace(line.find("(:"), 2, "(");
    //std::cout << line << std::endl;
    line = tryRemoveBrackets(line);
    std::string keyNames[3] = {"key1", "key2", "key3"};
    return_tuple tuple = parseLine(line, ":", " ", keyNames);
    //std::cout << "tuple: " << std::get<0>(tuple) << " " << std::get<1>(tuple).first << " " << std::get<1>(tuple).second
    //          << std::get<2>(tuple) << " " << std::endl;
    ds.emplace_back(tuple);
  }
  std::sort(ds.begin(), ds.end(), compareK1);
  std::for_each(ds.begin(), ds.end(), print);
  return 0;
}
