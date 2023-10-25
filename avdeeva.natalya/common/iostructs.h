#ifndef SPBSPU_LABS_2023_TP_904_A_IOSTRUCTS_H
#define SPBSPU_LABS_2023_TP_904_A_IOSTRUCTS_H
#include <string>
#include <iostream>

namespace avdeeva
{
  struct DelimiterIO
  {
    char exp;
  };
  struct DoubleI
  {
    double & num;
  };
  struct DoubleO
  {
    const double num;
  };
  struct UnsignedLongLongIO
  {
    unsigned long long & num;
  };
  struct StringIO
  {
    std::string & exp;
  };
  struct LabelIO
  {
    std::string exp;
  };
  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  std::istream & operator>>(std::istream & in, LabelIO && dest);
  std::istream & operator>>(std::istream & in, StringIO && dest);
  std::istream & operator>>(std::istream & in, UnsignedLongLongIO && dest);
  std::istream & operator>>(std::istream & in, DoubleI && dest);
  std::ostream & operator<<(std::ostream & out, const DoubleO && dest);
}
#endif
