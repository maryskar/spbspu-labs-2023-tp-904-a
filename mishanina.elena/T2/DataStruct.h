#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <iostream>

namespace mishanina
{
  struct DataStruct
  {
    DataStruct():
      key1(0),
      key2(0),
      key3("")
    {}
    long long key1;
    unsigned long long key2;
    std::string key3;
  };
  std::ostream &printLL(std::ostream &out,  const long long &data);
  std::ostream &printULL(std::ostream &out, const unsigned long long &data);
  std::istream &operator>>(std::istream &in, DataStruct &data);
  std::ostream &operator<<(std::ostream &out, const DataStruct &data);
  struct Comparator{
    bool operator()(const DataStruct &left, const DataStruct &right);
  };
}
#endif
