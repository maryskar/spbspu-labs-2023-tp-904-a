#include "datastruct.h"
DataStruct::DataStruct(unsigned long long int key1, std::pair<long long, unsigned long long> key2, std::string key3) :
  key1(key1),
  key2(std::move(key2)),
  key3(std::move(key3))
{
}