#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <string>

namespace structure {
  struct DataStruct {
    double key1;
    long long key2;
    std::string key3;
  };
  std::ostream& operator<<(std::ostream& os, const DataStruct& data);
  std::istream& operator>>(std::istream& in, DataStruct& src);
  bool operator<(const DataStruct& left, const DataStruct& right);
}

#endif
