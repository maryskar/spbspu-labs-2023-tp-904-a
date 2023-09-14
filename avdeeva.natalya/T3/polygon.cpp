#include "polygon.h"
#include <algorithm>
#include "iostructs.h"
std::istream & avdeeva::operator>>(std::istream & in, const Point & rhs)
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
    rhs = input;
  }
  return in;
}
std::istream & avdeeva::operator>>(std::istream & in, const Polygon & rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Polygon input;
  size_t verts = 0;
  in >> verts;
  if (!in || verts < 3)
  {
    in.setstate(std::ios::failbit);
  }
  input.points.reserve(verts);
  using inIter = std::istream_iterator< Point >;
  std::copy_n(inIter(in), verts, std::back_inserter(input.points));
  if (in)
  {
    rhs.points.swap(input.points);
  }
  return in;
}
size_t avdeeva::size(const Polygon &pol)
{
  return pol.points.size();
}
double avdeeva::areaCounter(const Point & lhs, const Point & rhs)
{
  return 0.5 * (lhs.x * rhs.y - rhs.x * lhs.y);
}
double avdeeva::getArea(const Polygon & pol)
{
  double area = 0.0;
  std::vector< double > values(size(pol));
  std::transform(pol.points.begin(), --pol.points.end(), ++pol.points.begin(), std::back_inserter(values), areaCounter);
  area = std::accumulate(values.begin(), values.end(), 0.0);
  int x1 = (--pol.points.end())->x;
  int x2 = pol.points.begin()->x;
  int y1 = (--pol.points.end())->y;
  int y2 = pol.points.begin()->y;
  area += 0.5 * std::abs(x1 * y2 - x2 * y1);
  return area;
}