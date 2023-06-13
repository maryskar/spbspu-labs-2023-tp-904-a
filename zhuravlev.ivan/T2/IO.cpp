#include "IO.hpp"
#include "iofmtguard.hpp"
#include <iomanip>

namespace zhuravlev
{
  std::istream& operator>>(std::istream& in, DelimetrIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.expression))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream& in, BinIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> DelimetrIO{ '0b' } >> dest.ref;
  }

  std::istream &operator>>(std::istream& in, HexIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> std::hex >> dest.ref;
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimetrIO{ '"' }, dest.ref, '"');
  }

  std::istream &operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.expression))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
