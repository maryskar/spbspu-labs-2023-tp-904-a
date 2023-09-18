#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <iomanip>

namespace kabanov
{
  struct DataStruct
  {
    unsigned long long key1;
    char key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
  bool comp(const DataStruct& lhs, const DataStruct& rhs);
}
#endif
