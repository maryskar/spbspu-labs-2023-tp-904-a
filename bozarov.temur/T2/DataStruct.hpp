#ifndef T2_DATASTRUCT_HPP
#define T2_DATASTRUCT_HPP
#include <complex>
#include <string>

  namespace bozarov
  {
    struct DataStruct
    {
      unsigned long long key1;
      std::complex< double > key2;
      std::string key3;
    };
    bool compare(const DataStruct& lhs, const DataStruct& rhs);
    std::istream& operator>>(std::istream& is, DataStruct& data);
    std::ostream& operator<<(std::ostream& out, const DataStruct& data);
  }
#endif
