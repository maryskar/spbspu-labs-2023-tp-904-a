#include "point.h"
#include <iotypes.h>

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
