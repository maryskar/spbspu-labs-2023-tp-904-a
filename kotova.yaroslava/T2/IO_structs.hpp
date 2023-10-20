#ifndef IO_STRUCTS_HPP
#define IO_STRUCTS_HPP
#include <string>

namespace kotova
{
  struct DelimiterIO
  {
    char exp;
  };

   struct DoubleI
  {
    double &ref;
  };

  struct DoubleO
  {
    const double res;
  };

  struct ULLHexIO
  {
    unsigned long long &num;
  };

  struct StringIO
  {
    std::string &ref;
  };

  struct LabelIO
  {
    std::string exp;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, DoubleI &&dest);
  std::ostream &operator<<(std::ostream &out, const DoubleO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, ULLHexIO &&dest);
}
#endif
