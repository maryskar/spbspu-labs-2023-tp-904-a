#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <bitset>

namespace tarasenko
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& dest);

  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}
#endif
