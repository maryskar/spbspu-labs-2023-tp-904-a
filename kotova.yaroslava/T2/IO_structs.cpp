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
    in >> std::scientific >> dest.ref;
    return in;
  }

  std::ostream &operator<<(std::ostream &out, DoubleO &&dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    double data = dest.res;
    int exp = 0;
    if (data >= 10)
    {
      while (data >= 10)
      {
        data /= 10;
        exp++;
      }
    }
    else
    {
      while (data < 1)
      {
        data *= 10;
        exp--;
      }
    }
    out << std::fixed << std::setprecision(1) << data << (exp > 0 ? "e+" : "e") << exp;
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
    return std::getline(in >> DelimiterIO{':'}, dest.exp, ' ');
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
