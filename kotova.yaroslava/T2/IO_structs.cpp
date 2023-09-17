#include "IO_structs.hpp"
#include <cmath>
#include <iomanip>
#include "iofmtguard.hpp"

namespace kotova
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, DoubleI &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> std::scientific >> dest.ref;
  }

  std::ostream &operator<<(std::ostream &out, const DoubleO &&dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    double data = dest.res;
    int exp = 0;
    while (std::abs(data) >= 10 || std::abs(data) < 1)
    {
      if (std::abs(data) >= 1)
      {
        data /= 10;
        exp++;
      }
      else if (std::abs(data) <= 1)
      {
        data *= 10;
        exp--;
      }
    }
    return out << std::fixed << std::setprecision(1) << data << (exp > 0 ? "e+" : "e") << exp;
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
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

  std::istream & operator>>(std::istream &in, ULLHexIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> std::hex >> dest.num;
    return in;
  }
}
