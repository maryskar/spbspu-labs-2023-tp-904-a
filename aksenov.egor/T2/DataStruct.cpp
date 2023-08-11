#include "DataStruct.h"
namespace aksenov
{
  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
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
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, ComplexIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    double real = 0.0;
    double imag = 0.0;
    in >> LabelIO{"#c("} >> real >> imag >> DelimiterIO{')'};
    return in;
  }

  std::istream &operator>>(std::istream &in, UllIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> dest.ref;
    return in;
  }
}
