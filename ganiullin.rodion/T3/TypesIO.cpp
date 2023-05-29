#include "TypesIO.h"

#include <cmath>
#include <iomanip>

std::istream& ganiullin::operator>>(std::istream& in,
    ganiullin::DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}
