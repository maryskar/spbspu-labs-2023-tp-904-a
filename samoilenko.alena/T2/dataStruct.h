#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <complex>

namespace samoilenko
{
  struct DataStruct
  {
    unsigned long long key1;
    std::complex< double > key2;
    std::string key3;
  };
  bool compareData(const DataStruct& lhs, const DataStruct& rhs);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}

#endif
