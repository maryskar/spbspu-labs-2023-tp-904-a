#include <string>
#include <iostream>
#include <tuple> //(:key1 10ull:key2 (:N -1:D 5:):key3 "Data":)
#include <vector>
#include "datastruct.h"
#include "input.h"
using return_tuple = std::tuple<unsigned long long, std::pair<long long, unsigned long long>, std::string>;
using string_pair = std::tuple<std::string, std::string>;
int main()
{
  for (std::string line; std::getline(std::cin, line);)
  {
    line = tryRemoveBrackets(line);
    std::string keyNames[3] = {"key1", "key2", "key3"};
    return_tuple tuple = parseLine(line, ":", " ", keyNames);
    std::vector<DataStruct> ds;
    ds.emplace_back(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple));
  }
  return 0;
}
