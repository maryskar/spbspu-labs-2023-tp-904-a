#include "polygon.h"
#include <iostream>

bool skarlygina::operator==(const Polygon& lhs, const Polygon& rhs)
{
  return (lhs.points == rhs.points);
}

bool skarlygina::operator!=(const Polygon& lhs, const Polygon& rhs)
{
  return !(lhs == rhs);
}

std::istream& skarlygina::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
}

std::ostream& skarlygina::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
}

