#include "IO.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <string>
#include <bitset>

namespace zhuravlev
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && dest.expected)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

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
    in >> dest.ref;
    return in;
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
  std::istream &operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    for (size_t i = 0; i < dest.exp.length(); i++)
    {
      in >> DelimiterIO{dest.exp[i]};
    }
    return in;
  }
}
