#include "IOstructs.h"
#include <iomanip>
#include <string>
#include <cmath>

namespace kryuchkova
{
  std::istream & operator>>(std::istream & in, Delimiter && dest)
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

  std::istream & operator>>(std::istream & in, DblSci && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    int a = 0;
    int b = 0;
    int power = 0;
    in >> a >> Delimiter{'.'} >> b >> Delimiter{'e'} >> power;
    double mantissa = a + static_cast< double >(b) / 10;
    dest.ref = mantissa * std::pow(10, power);
    return in;
  }

  std::istream & operator>>(std::istream & in, UllOct && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> std::oct >> dest.ref;
    return in;
  }

  std::istream & operator>>(std::istream & in, String && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> Delimiter{'"'}, dest.ref, '"');
  }

  std::istream & operator>>(std::istream & in, Label && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    for (size_t i = 0; i < dest.exp.length(); i++)
    {
      in >> Delimiter{dest.exp[i]};
    }
    return in;
  }

}
