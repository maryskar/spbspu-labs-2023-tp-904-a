#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <istream>
#include <iterator>
#include <algorithm>
#include "iodel.h"
namespace mishanina
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector<Point> points;
  };
  std::istream &operator>>(std::istream &in, Point &point);
  std::istream &operator>>(std::istream &in, Polygon &data);
  std::ostream &operator<<(std::ostream &out, const Point &data);
  std::ostream &operator<<(std::ostream &out, const Polygon &data);
}
std::istream &mishanina::operator>>(std::istream &in, Point &point)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> DelimiterIO{ '(' } >> point.x >> DelimiterIO{ ';' } >> point.y >> DelimiterIO{ ')' };
}

std::istream &mishanina::operator>>(std::istream &in, Polygon &data){
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  std::size_t count = 0;
  in >> count;
  if (count < 3) {
    in.setstate(std::ios::failbit);
    return in;
  }
  Polygon polygon;
  polygon.points.resize(count);
  std::copy_n(std::istream_iterator<Point>(in), count, std::begin(polygon.points));
  if (in) {
    data = polygon;
  }
  return in;
}


#endif
