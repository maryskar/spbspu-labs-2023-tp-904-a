#include "Polygon.h"
std::istream &mishanina::operator>>(std::istream &in, Point &point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point input{0, 0};
  in >> DelimiterIO{'('} >> input.x >> DelimiterIO{';'} >> input.y >> DelimiterIO{')'};
  if (in)
  {
    point = input;
  }
  return in;
}

std::istream &mishanina::operator>>(std::istream &in, Polygon &data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  Polygon pol;
  pol.points.reserve(count);
  std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(pol.points));
  if (in)
  {
    data.points.swap(pol.points);
  }
  return in;
}
bool mishanina::operator==(const Point &left, const Point &right)
{
  return (left.x == right.x && left.y == right.y);
}
