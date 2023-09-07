#ifndef STRUCT_IO_H
#define STRUCT_IO_H
#include <string>

namespace skarlygina
{
  struct delimiter_sep_t
  {
    char sep;
  };

  struct delimiter_IO_t
  {
    char exp;
  };

  struct string_IO_t
  {
    std::string& ref;
  };

  struct DBL_sciIO_t
  {
    double& ref;
  };

  struct ULL_hexIO_t
  {
    unsigned long long& ref;
  };


  std::istream& operator>>(std::istream& in, delimiter_sep_t&& dest);
  std::istream& operator>>(std::istream& in, delimiter_IO_t&& dest);
  std::istream& operator>>(std::istream& in, string_IO_t&& dest);
  std::istream& operator>>(std::istream& in, DBL_sciIO_t&& dest);
  std::istream& operator>>(std::istream& in, ULL_hexIO_t&& dest);
  std::ostream& operator<<(std::ostream& out, const DBL_sciIO_t& dest);
}
#endif
