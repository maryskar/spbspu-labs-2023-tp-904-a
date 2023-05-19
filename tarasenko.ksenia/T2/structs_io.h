#ifndef STRUCTS_IO_H
#define STRUCTS_IO_H

#include <iostream>
#include <string>

namespace tarasenko
{
  struct DelimiterIO
  {
    char exp;
  };

  struct LabelIO
  {
    std::string exp;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct ULLIO
  {
    unsigned long long& ref;
  };

  struct ULLBinIO
  {
    std::bitset< 64 >& ref;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, ULLIO&& dest);
  std::istream& operator>>(std::istream& in, ULLBinIO&& dest);
}
#endif
