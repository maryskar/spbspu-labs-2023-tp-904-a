#ifndef SPBSPU_LABS_2023_TP_904_A_IO_TYPES_HPP
#define SPBSPU_LABS_2023_TP_904_A_IO_TYPES_HPP
#include "data_struct.hpp"

namespace zhuravlev
{
  struct DelimiterIO
  {
    char expected;
  };
  struct HexIO
  {
    unsigned long long& ref;
  };
  struct BinIO
  {
    unsigned long long& ref;
  };
  struct StringIO
  {
    std::string& ref;
  };
  struct LabelIO
  {
    std::string exp;
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, HexIO&& dest);
  std::istream& operator>>(std::istream& in, BinIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
}
#endif
