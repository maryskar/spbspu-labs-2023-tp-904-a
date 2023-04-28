#include <iostream>
#include "datastruct.h"
#include "input.h"
DataStruct::DataStruct(unsigned long long int key1, std::pair<long long, unsigned long long> key2, std::string key3) :
  key1(key1),
  key2(std::move(key2)),
  key3(std::move(key3))
{
}
DataStruct::DataStruct(return_tuple tuple) :
  key1(std::get<0>(tuple)),
  key2(std::get<1>(tuple)),
  key3(std::get<2>(tuple))
{
}
void DataStruct::printDS() const
{
  std::cout << "(:key1 0" << key1 << ":key2 (:N " << key2.first << ":D " << key2.second << ":):key3 " << key3 << ":)\n";
}
