#ifndef SPBSPU_LABS_2023_TP_904_A_IO_HPP
#define SPBSPU_LABS_2023_TP_904_A_IO_HPP
#include <string>
#include <sstream>
#include "data_struct.hpp"

namespace zhuravlev
{
 struct DelimetrIO
 {
   char expression;
 };

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

  struct LabelIO
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, DelimetrIO&& dest);
  std::istream& operator>>(std::istream& in, BinIO&& dest);
  std::istream& operator>>(std::istream& in, HexIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
}
#endif
