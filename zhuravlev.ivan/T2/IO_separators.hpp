#ifndef SPBSPU_LABS_2023_TP_904_A_IO_BIN_HEX_STR_TYPES_HPP
#define SPBSPU_LABS_2023_TP_904_A_IO_BIN_HEX_STR_TYPES_HP
#include "data_struct.hpp"

namespace zhuravlev
{
  struct DelimiterIO
  {
    char expected;
  };
  struct LabelIO
  {
    std::string exp;
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
}
#endif
