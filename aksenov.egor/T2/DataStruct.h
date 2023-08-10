#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <string>
#include <iostream>
#include <complex>
namespace aksenov {
  struct DataStruct
  {
    unsigned long long key1;
    std::complex< double > key2;
    std::string key3;
  };
  std::istream &operator>>(std::istream &in, DataStruct &dst);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dst);
}
#endif
