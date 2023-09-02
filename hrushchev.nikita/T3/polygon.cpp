#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <iotypes.hpp>

std::istream& hrushchev::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{'('};
  in >> dest.x_;
  in >> DelimiterIO{';'};
  in >> dest.y_;
  in >> DelimiterIO{')'};
  return in;
}

std::istream& hrushchev::operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  using iter = std::istream_iterator< Point >;
  std::copy_n(iter(in), count, std::back_inserter(dest.points_));
  return in;
}
