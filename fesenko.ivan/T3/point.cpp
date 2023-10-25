#include "point.h"
#include <iotypes.h>
#include <iofmtguard.h>

std::istream &fesenko::operator>>(std::istream &in, Point &rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  Point input{0, 0};
  using del = DelimiterIO;
  in >> del{ '(' } >> input.x >> del{ ';' } >> input.y >> del{ ')' };
  if (in) {
    rhs = input;
  }
  return in;
}

std::ostream &fesenko::operator<<(std::ostream &out, const Point &rhs)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  iofmtguard fmtguard(out);
  return out << '(' << rhs.x << ';' << rhs.y << ')';
}
