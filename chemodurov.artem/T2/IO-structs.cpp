#include "IO-structs.hpp"
#include <cmath>
#include "iofmtguard.hpp"

namespace chemodurov
{
  std::istream & operator>>(std::istream & in, DelimiterIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '\0';
    in >> c;
    if (in && c != std::tolower(dest.exp) && c != std::toupper(dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream & operator>>(std::istream & in, DoubleIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    int a = 0;
    int b = 0;
    int power = 0;
    in >> a >> DelimiterIO{'.'} >> b >> DelimiterIO{'e'} >> power;
    double mantissa = a + static_cast< double >(b) / 10;
    dest.ref = mantissa * std::pow(10, power);
    return in;
  }

  std::istream & operator>>(std::istream & in, LongLongIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{'l'} >> DelimiterIO{'l'};
  }

  std::istream & operator>>(std::istream & in, StringIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }

  std::istream & operator>>(std::istream & in, LabelIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{':'}, dest.ref, ' ');
  }
}
