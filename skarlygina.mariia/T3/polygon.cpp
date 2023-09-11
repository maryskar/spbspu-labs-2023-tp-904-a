#include "polygon.h"
#include <iostream>
#include <algorithm>
#include <iterator>

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
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  size_t num = 0;
  in >> num;
  if (num < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  using in_iter = std::istream_iterator< Point >;
  std::vector< Point > temp;
  std::copy_n(in_iter(in), num, std::back_inserter(temp));
  if (in)
  {
    polygon.points = temp;
  }
  return in;
}

std::ostream& skarlygina::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << polygon.points.size() << ' ';
  using out_iter = std::ostream_iterator< Point >;
  std::copy(polygon.points.cbegin(), polygon.points.cend(), out_iter(out, " "));
  return out;
}

