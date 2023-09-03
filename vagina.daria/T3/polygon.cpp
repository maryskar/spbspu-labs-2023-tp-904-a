#include "polygon.h"
#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <TypesIO.h>

std::istream& vagina::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' } >> dest.y >> DelimiterIO{ ')' };
  return in;
}
std::istream& vagina::operator>>(std::istream& in, Polygon& dest)
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
  Polygon polygon;
  polygon.points.resize(count);
  std::copy_n(std::istream_iterator< Point >(in), count, std::begin(polygon.points));
  if (in)
  {
    dest = polygon;
  }
  return in;
}
double vagina::getArea(const Polygon& dest)
{
  double area;
  auto getPoint = [&](Point a, Point b)
  {
    return a.x * b.y - a.y * b.x;
  };
  std::vector< int > arr(dest.points.size());
  std::transform(dest.points.begin(), --dest.points.end(), ++dest.points.begin(), std::back_inserter(arr), getPoint);
  area = std::accumulate(arr.begin(), arr.end(), 0.0);
  area += (--dest.points.end())->x * dest.points.begin()->y - dest.points.begin()->x * (--dest.points.end())->y;
  return std::abs(area * 0.5);
}
bool vagina::comparatorArea(const Polygon& lhs, const Polygon& rhs)
{
  return (getArea(lhs) > getArea(rhs));
}
bool vagina::comparatorVertexes(const Polygon& lhs, const Polygon& rhs)
{
  return (lhs.points.size() > rhs.points.size());
}
bool vagina::isParallelogram(const Polygon& dest)
{
  if (dest.points.size() == 4)
  {
    Point p1 = dest.points[0];
    Point p2 = dest.points[1];
    Point p3 = dest.points[2];
    Point p4 = dest.points[3];
    return (((p2.x - p1.x) == (p3.x - p4.x)) && ((p4.y - p1.y) == (p3.y - p2.y)));
  }
  return false;
}
bool vagina::isRectangle(const Polygon& dest)
{
  if (dest.points.size() == 4)
  {
    Point p1 = dest.points[0];
    Point p2 = dest.points[1];
    Point p3 = dest.points[2];
    Point p4 = dest.points[3];
    auto firstSide = std::pow(p2.x - p1.x, 2);
    auto secondSide = std::pow(p4.y - p1.y, 2);
    auto thirdSide = std::pow(p3.y - p2.y, 2);
    auto fourthSide = std::pow(p3.x - p4.x, 2);
    if (isParallelogram(dest))
    {
      return (firstSide + secondSide) == (thirdSide + fourthSide);
    }
  }
  return false;
}
bool vagina::operator==(const Point& lhs, const Point& rhs)
{
  return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}
