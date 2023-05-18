#ifndef IO_STRUCTS_HPP
#define IO_STRUCTS_HPP
#include <string>

namespace kotova
{
  struct DelimiterIO
  {
    char exp;
  };

   struct DoubleIO
  {
    double &ref;
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
  std::istream &operator>>(std::istream &in, DoubleIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
}
#endif
