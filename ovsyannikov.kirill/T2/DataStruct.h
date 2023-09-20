#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <iostream>
#include <string>

namespace ovsyannikov
{
  struct DataStruct
  {
    unsigned long long key1;
    char key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

  struct Comparator
  {
    bool operator()(const DataStruct& data1, const DataStruct& data2) const;
  };
}
#endif
