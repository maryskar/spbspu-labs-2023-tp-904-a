#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <string>

namespace kryuchkova
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream & operator>>(std::istream & in, DataStruct & dest);
  std::ostream & operator<<(std::ostream & out, const DataStruct & source);
  bool cmpData(const DataStruct & lhs, const DataStruct & rhs);
}

#endif
