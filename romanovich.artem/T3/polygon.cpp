#include "polygonutils.h"
namespace
{
  struct DelimiterIO
  {
    char symbol;
  };
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.symbol))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, Point &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> DelimiterIO{'('} >> dest.x >> DelimiterIO{';'};
    in >> dest.y >> DelimiterIO{')'};
    return in;
  }
}
std::istream &romanovich::operator>>(std::istream &in, Polygon &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t pointsCount;
  in >> pointsCount;
  std::vector< Point > polygon;
  for (size_t i = 0; i < pointsCount; i++)
  {
    romanovich::Point point{0, 0};
    in >> point;
    if (std::find(polygon.begin(), polygon.end(), point) == polygon.end())
    {
      in.setstate(std::ios::failbit);
    }
    polygon.push_back(point);
  }
  if (polygon.size() != pointsCount || polygon.size() <= 2)
  {
    in.setstate(std::ios::failbit);
  }
  if (in)
  {
    dest = Polygon{polygon};
  }
  return in;
}
size_t romanovich::getPointsCount(const Polygon &p)
{
  return p.points.size();
}
double romanovich::getArea(const Polygon &p)
{
  double area = 0.0;
  size_t n = getPointsCount(p);
  if (n >= 3)
  {
    size_t j = n - 1;
    for (size_t i = 0; i < n; i++)
    {
      area += (p.points[j].x + p.points[i].x) * (p.points[j].y - p.points[i].y);
      j = i;
    }
    return std::abs(area / 2.0);
  }
  return 0;
}
bool romanovich::operator==(const Polygon &lhs, const Polygon &rhs)
{
  if (getPointsCount(lhs) != getPointsCount(rhs))
  {
    return false;
  }
  for (size_t i = 0; i < getPointsCount(lhs); ++i)
  {
    if (lhs.points[i] != rhs.points[i])
    {
      return false;
    }
  }
  return true;
}
typename std::vector< romanovich::Point >::const_iterator romanovich::begin(const Polygon &p)
{
  return p.points.begin();
}
typename std::vector< romanovich::Point >::const_iterator romanovich::end(const Polygon &p)
{
  return p.points.end();
}
