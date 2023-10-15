#ifndef SPBSPU_LABS_2023_TP_904_AM_DATA_STRUCT_H
#define SPBSPU_LABS_2023_TP_904_AM_DATA_STRUCT_H
#include <string>
#include <complex>

namespace shestakov
{
  struct DataStruct
  {
    char key1;
    std::complex< double > key2;
    std::string key3;
  };
  bool compareValues(const DataStruct& lhs, const DataStruct& rhs);
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}
#endif
