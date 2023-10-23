#include "IO_bin_hex_str.hpp"
#include <iomanip>
#include <string>
#include "IO_separators.hpp"
#include "iofmtguard.hpp"

namespace zhuravlev
{
  std::istream& operator>>(std::istream& in, HexIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> std::hex >> dest.ref;
  }

  std::istream& operator>>(std::istream& in, BinIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> DelimiterIO{ '0' } >> DelimiterIO{ 'b' } >> dest.ref;
  }
  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }
}
