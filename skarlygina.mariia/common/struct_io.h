#ifndef STRUCT_IO_H
#define STRUCT_IO_H
#include <iosfwd>
namespace skarlygina
{
  struct DelimiterIO
  {
    char exp;
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}
#endif
