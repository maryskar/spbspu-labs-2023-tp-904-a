#ifndef T2_DATASTRUCT_H
#define T2_DATASTRUCT_H
#include <complex>
namespace zhukova
{
  struct DataStruct
  {
    std::complex< double > key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };
  struct Comparator
  {
    bool operator()(const DataStruct & lhs, const DataStruct & rhs) const;
  };
}
#endif
