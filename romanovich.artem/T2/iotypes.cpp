#include "iotypes.h"
#include <iostream>
namespace romanovich
{
  std::istream &operator>>(std::istream &in, UnsignedLongLongIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> DelimiterIO{'0'} >> dest.number;
  }
  std::istream &operator>>(std::istream &in, RationalNumberIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> DelimiterIO{'('} >> DelimiterIO{':'};
    in >> DelimiterIO{'N'} >> dest.ratNumber.first;
    in >> DelimiterIO{':'};
    in >> DelimiterIO{'D'} >> dest.ratNumber.second;
    return in >> DelimiterIO{':'} >> DelimiterIO{')'};
  }
  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.string, '"');
  }
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.symbol))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
