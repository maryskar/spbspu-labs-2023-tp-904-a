#ifndef SPBSPU_LABS_2023_TP_904_A_IO_HPP
#define SPBSPU_LABS_2023_TP_904_A_IO_HPP
#include <string>
#include <sstream>
#include "data_struct.hpp"

namespace zhuravlev
{
  struct Delimiter
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
}
#endif
