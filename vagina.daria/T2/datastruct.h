#ifndef T2_DATASTRUCT_H
#define T2_DATASTRUCT_H
#include <iostream>

namespace vagina
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
  bool comp(const DataStruct& lhs, const DataStruct& rhs);
}

#endif
