#ifndef SPBSPU_LABS_2023_TP_904_A_DATA_STRUCT_HPP
#define SPBSPU_LABS_2023_TP_904_A_DATA_STRUCT_HPP
#include <string>

namespace zhuravlev
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  bool compareData(const DataStruct& lhs, const DataStruct& rhs);
  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}
#endif
