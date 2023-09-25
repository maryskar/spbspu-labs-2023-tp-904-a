#include "point.h"
#include <iostream>
#include <struct_io.h>

std::istream& skarlygina::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  in >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'} >> point.y >> DelimiterIO{')'};
  return in;
}

std::ostream& skarlygina::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

bool skarlygina::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool skarlygina::operator!=(const Point& lhs, const Point& rhs)
{
  return !(lhs == rhs);
}

skarlygina::Point skarlygina::operator+(const Point& lhs, const Point& rhs)
{
  return {lhs.x + rhs.x, lhs.y + rhs.y};
}
