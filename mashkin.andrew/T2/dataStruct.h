#ifndef T2_DATASTRUCT_H
#define T2_DATASTRUCT_H
#include <iostream>
#include <string>

namespace mashkin
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };
  //bool comp(const DataStruct& first, const DataStruct& second);
  std::istream& operator>>(std::istream& inp, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}
#endif
