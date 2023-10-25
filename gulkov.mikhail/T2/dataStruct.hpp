#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>

namespace gulkov
{
  struct DataStruct
  {
    unsigned long long key1;
    char key2;
    std::string key3;
  };

  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
  std::istream& operator>>(std::istream& in, DataStruct& data);

  struct Comparator
  {
    bool operator()(const DataStruct& data1, const DataStruct& data2);
  };
}
#endif
