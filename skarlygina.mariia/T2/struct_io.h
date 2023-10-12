#ifndef STRUCT_IO_H
#define STRUCT_IO_H
#include <string>

namespace skarlygina
{
  struct DelimiterSep
  {
    char sep;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct DBLsciI
  {
    double& ref;
  };

  struct DBLsciO
  {
    const double& ref;
  };

  struct ULLhexI
  {
    unsigned long long& ref;
  };

  struct ULLhexO
  {
    const unsigned long long& ref;
  };

  std::istream& operator>>(std::istream& in, DelimiterSep&& dest);
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, DBLsciI&& dest);
  std::istream& operator>>(std::istream& in, ULLhexI&& dest);
  std::ostream& operator<<(std::ostream& out, ULLhexO&& dest);
  std::ostream& operator<<(std::ostream& out, const DBLsciO& dest);
  std::ostream& operator<<(std::ostream& out, const StringIO& dest);
}
#endif
