#ifndef IO_SEPARATORS_HPP
#define IO_SEPARATORS_HPP
#include <string>

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
