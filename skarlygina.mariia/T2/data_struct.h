#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <string>

namespace skarlygina
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };
  std::ostream& operator<<(std::ostream& os, const DataStruct& data);
  std::istream& operator>>(std::istream& in, DataStruct& data);
  bool operator<(const DataStruct& left, const DataStruct& right);
}

#endif

