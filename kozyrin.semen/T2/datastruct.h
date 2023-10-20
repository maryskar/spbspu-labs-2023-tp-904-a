#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <iostream>

namespace kozyrin
{
  struct DataStruct {
    double key1;
    unsigned long long key2;
    std::string key3;
  };

  bool comp(const DataStruct& lhs, const DataStruct& rhs);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}

#endif
