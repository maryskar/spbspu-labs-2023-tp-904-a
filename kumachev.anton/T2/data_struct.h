#ifndef T2_DATA_STRUCT_H
#define T2_DATA_STRUCT_H

#include <string>

namespace kumachev {
  using rational = std::pair< long long, unsigned long long >;

  struct DataStruct {
    unsigned long long key1;
    rational key2;
    std::string key3;
  };

  struct DataStructComparator {
    bool operator()(const DataStruct &lhs, const DataStruct &rhs) const;
  };
}

#endif
