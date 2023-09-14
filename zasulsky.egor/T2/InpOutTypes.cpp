#include "InpOutTypes.hpp"

std::istream& operator>>(std::istream& in, DelimiterIO&& ref)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (c != ref.exp && in)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const DelimiterIO& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  return out << data.exp;
}
