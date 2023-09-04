#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <complex>
#include <string>

namespace structure {
  struct DataStruct {
    long long key1;
    std::complex< double > key2;
    std::string key3;
  };
  std::ostream& operator<<(std::ostream& os, const DataStruct& data);
  std::istream& operator>>(std::istream& in, DataStruct& src);
  size_t getDataStructSize();
}

#endif // !DATA_STRUCT_H

