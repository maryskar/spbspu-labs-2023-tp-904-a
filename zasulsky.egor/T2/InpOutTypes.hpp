#ifndef INPOUTTYPES_HPP
#define INPOUTTYPES_HPP


#include <string>
#include <iostream>

namespace zasulsky
{
  struct DelimiterIO
  {
    char exp;
  };
  struct DoubleI
  {
    double& num;
  };
  struct DoubleO
  {
    const double num;
  };
  struct LongLongIO
  {
     long long& num;
  };
  struct StringIO
  {
    std::string& exp;
  };
  struct LabelIO
  {
    std::string exp;
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LongLongIO&& dest);
  std::istream& operator>>(std::istream& in, DoubleI&& dest);
  std::ostream& operator<<(std::ostream& out, const DoubleO&& dest);
}
#endif
