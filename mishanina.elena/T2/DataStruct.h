#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <iostream>
#include <iotypes.h>
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
  std::ostream &operator<<(std::ostream &out, const LongLongIO &dest);
  std::ostream &operator<<(std::ostream &out, const UnsignedLongLongIO &dest);
  std::istream &operator>>(std::istream &in, DataStruct &data);
  std::ostream &operator<<(std::ostream &out, const DataStruct &data);
  struct Comparator{
    bool operator()(const DataStruct &left, const DataStruct &right);
  };
}
#endif
