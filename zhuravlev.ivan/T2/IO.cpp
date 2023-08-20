#include "IO.hpp"
#include "iofmtguard.hpp"
#include <iomanip>

std::istream& operator>>(std::istream& in, zhuravlev::DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && c != dest.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, zhuravlev::HexIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> zhuravlev::DelimiterIO{ '0x' } >> dest.ref;
}
