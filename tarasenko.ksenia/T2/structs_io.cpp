#include <bitset>
#include "structs_io.h"

std::istream& tarasenko::operator>>(std::istream& in, DelimiterIO&& dest)
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

std::istream& tarasenko::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}

std::istream& tarasenko::operator>>(std::istream& in, LiteralIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string lit = "";
  std::getline(in, lit, ':');
  in.putback(':');
  if (in && (lit != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& tarasenko::operator>>(std::istream& in, ULLIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref >> LiteralIO{"ull"};
}

std::istream& tarasenko::operator>>(std::istream& in, ULLBinIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char buf[3];
  std::cin.get(buf, 3);
  if (in && buf[0] != 0 && buf[1] != 'b' && buf[1] != 'B')
  {
    in.setstate(std::ios::failbit);
  }
  std::bitset< 64 > num;
  in >> num;
  dest.ref = num.to_ullong();
  return in;
}
