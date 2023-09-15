#ifndef SPBSPU_LABS_2023_TP_904_A_IO_BIN_HEX_STR_TYPES_HPP
#define SPBSPU_LABS_2023_TP_904_A_IO_BIN_HEX_STR_TYPES_HP
#include "data_struct.hpp"

namespace zhuravlev
{
  struct BinIO
  {
    unsigned long long& ref;
  };
  struct HexIO
  {
    unsigned long long& ref;
  };
  struct StringIO
  {
    std::string& ref;
  };
  std::istream& operator>>(std::istream& in, BinIO&& dest);
  std::istream& operator>>(std::istream& in, HexIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}
#endif
