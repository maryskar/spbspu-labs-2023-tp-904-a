#ifndef SPBSPU_LABS_2023_TP_904_A_DATA_STRUCT_HPP
#define SPBSPU_LABS_2023_TP_904_A_DATA_STRUCT_HPP
#include <string>

namespace zhuravlev
{
  struct Data
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& in, Data&& dest);
  std::ostream& operator<<(std::ostream& out, const Data& dest);
  bool dataComparator(const Data& lhs, const Data& rhs);
}
#endif
