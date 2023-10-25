#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <string>

namespace zhdanov
{
  struct DataStruct
  {
    long long key1 = 0;
    unsigned long long key2 = 0;
    std::string key3 = "";
  };
  bool operator<(const DataStruct& a, const DataStruct& b);
  std::istream& operator>>(std::istream& input, DataStruct& data);
  std::ostream& operator<<(std::ostream& output, const DataStruct& data);
}
#endif
