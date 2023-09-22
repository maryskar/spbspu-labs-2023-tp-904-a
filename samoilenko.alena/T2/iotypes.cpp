#include "iotypes.h"

std::istream& samoilenko::operator>>(std::istream& in, Delimiter&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char a = '0';
  in >> a;
  if (in && (a != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
