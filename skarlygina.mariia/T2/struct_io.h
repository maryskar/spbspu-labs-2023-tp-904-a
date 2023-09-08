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

  struct DBL_sciI_t
  {
    double& ref;
  };

  struct DBL_sciO_t
  {
    double ref;
  };

  struct ULL_hexI_t
  {
    unsigned long long& ref;
  };

  struct ULL_hexO_t
  {
    unsigned long long ref;
  };

  std::istream& operator>>(std::istream& in, delimiter_sep_t&& dest);
  std::istream& operator>>(std::istream& in, delimiter_IO_t&& dest);
  std::istream& operator>>(std::istream& in, string_IO_t&& dest);
  std::istream& operator>>(std::istream& in, DBL_sciI_t&& dest);
  std::istream& operator>>(std::istream& in, ULL_hexI_t&& dest);
  std::ostream& operator<<(std::ostream& out, ULL_hexO_t&& dest);
  std::ostream& operator<<(std::ostream& out, const DBL_sciO_t& dest);
  std::ostream& operator<<(std::ostream& out, const string_IO_t& dest);
}
#endif
