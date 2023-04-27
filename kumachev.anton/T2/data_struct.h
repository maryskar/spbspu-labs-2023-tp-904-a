#ifndef T2_DATA_STRUCT_H
#define T2_DATA_STRUCT_H

#include <iosfwd>
#include <string>
#include <bits/stl_pair.h>

namespace T2 {
  struct DataStruct {
    unsigned long long key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
  };
}

std::istream &operator>>(std::istream &istream, T2::DataStruct &dataStruct);

#endif //T2_DATA_STRUCT_H
