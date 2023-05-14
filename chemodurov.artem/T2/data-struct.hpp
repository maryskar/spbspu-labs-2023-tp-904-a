#ifndef T2_DATA_STRUCT_HPP
#define T2_DATA_STRUCT_HPP
#include <string>

namespace chemodurov
{
  struct DataStruct
  {
    double key1;
    long long key2;
    std::string key3;
  };

  bool isLess(const DataStruct & lhs, const DataStruct & rhs);
  std::istream & operator>>(std::istream & in, DataStruct & data);
  std::ostream & operator<<(std::ostream & out, const DataStruct & data);
}

#endif
