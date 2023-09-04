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
  struct DoubleIO
  {
    double & num;
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
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
}
#endif
