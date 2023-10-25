#ifndef T2_DATASTRUCT_H
#define T2_DATASTRUCT_H

#include <string>

namespace nesterov
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);

  struct DataStructComparator
  {
    bool operator()(const DataStruct &lhs, const DataStruct &rhs) const;
  };
}

#endif
