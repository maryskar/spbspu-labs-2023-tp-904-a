#include "polygon.h"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cmath>
#include <iostructs.h>
bool avdeeva::operator==(const Point & lhs, const Point & rhs)
{
  return (lhs.x == rhs.x && lhs.y == rhs.y);
}
bool avdeeva::operator==(const Polygon & lhs, const Polygon & rhs)
{
  return (lhs.points.size() == rhs.points.size() && lhs.points == rhs.points);
}
std::istream & avdeeva::operator>>(std::istream & in, Point & rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  int x = 0;
  int y = 0;
  in >> DelimiterIO{'('} >> x >> DelimiterIO{';'} >> y >> DelimiterIO{')'};
  if (in)
  {
    rhs.x = x;
    rhs.y = y;
  }
  return in;
}
std::istream & avdeeva::operator>>(std::istream & in, Polygon & rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t verts = 0;
  in >> verts;
  if (!in || verts < 3)
  {
    in.setstate(std::ios::failbit);
  }
  std::vector< Point > polygon;
  polygon.reserve(verts);
  using inIter = std::istream_iterator< Point >;
  std::copy_n(inIter(in), verts, std::back_inserter(polygon));
  if (in)
  {
    rhs.points = polygon;
  }
  return in;
}
double avdeeva::areaCounter(const Point & lhs, const Point & rhs)
{
  return 0.5 * (lhs.x * rhs.y - rhs.x * lhs.y);
}
double avdeeva::getArea(const Polygon & pol)
{
  double area = 0.0;
  std::vector< double > values(pol.points.size());
  std::transform(pol.points.begin(), --pol.points.end(), ++pol.points.begin(), std::back_inserter(values), areaCounter);
  area = std::accumulate(values.begin(), values.end(), 0.0);
  int x1 = pol.points.back().x;
  int x2 = pol.points.front().x;
  int y1 = pol.points.back().y;
  int y2 = pol.points.front().y;
  area += 0.5 * (x1 * y2 - x2 * y1);
  return std::abs(area);
}
