#ifndef T2_DATASTRUCT_HPP
#define T2_DATASTRUCT_HPP
#include <complex>
#include <string>

namespace gulyaev
{
  struct DataStruct
  {
    unsigned long long key1;
    std::complex< double > key2;
    std::string key3;
  };

  bool isLess(const DataStruct &rhs, const DataStruct &lhs);
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
}
#endif
