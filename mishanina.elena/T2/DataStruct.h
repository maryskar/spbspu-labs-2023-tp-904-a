#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <iostream>
namespace mishanina
{
  struct DataStruct
  {
    long long key1;
    unsigned long long key2;
    std::string key3;
  };
  std::istream &operator>>(std::istream &in, DataStruct &data);
  std::ostream &operator<<(std::ostream &out, const DataStruct &data);
  struct Comparator
  {
    bool operator()(const DataStruct &left, const DataStruct &right);
  };
}
#endif
