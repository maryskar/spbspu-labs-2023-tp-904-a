#ifndef STRUCT_IO_H
#define STRUCT_IO_H
#include <iosfwd>
namespace skarlygina
{
  struct delimiter_IO_t
  {
    char exp;
  };
  std::istream& operator>>(std::istream& in, delimiter_IO_t&& dest);
}
#endif
