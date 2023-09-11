#include "datastructs.h"
#include <algorithm>
#include <numeric>
#include <limits>
#include <functional>
#include <iterator>

double azheganova::getTriangleArea(const Point & point1, const Point & point2)
{
  return point1.x * point2.y - point1.y * point2.x;
}

double azheganova::getArea(const Polygon & polygon)
{
  using namespace std::placeholders;
  size_t countOfPoints = polygon.points.size();
  std::vector< double > values(countOfPoints - 1);
  auto first = polygon.points.begin();
  auto second = first;
  second++;
  auto end = polygon.points.end();
  end--;
  auto oper = std::bind(getTriangleArea, _2, _1);
  std::transform(first, end, second, std::back_inserter(values), oper);
  double area = std::accumulate(values.begin(), values.end(), 0.0);
  area += oper(polygon.points.front(), polygon.points.back());
  area = std::abs(area) / 2;
  return area;
}

std::istream & azheganova::operator>>(std::istream & in, DelimiterIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & azheganova::operator>>(std::istream & in, Point & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' } >> dest.y >> DelimiterIO{ ')' };
  return in;
}
std::istream & azheganova::operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  Polygon polygon;
  std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(polygon.points));
  if (in)
  {
    dest = polygon;
  }
  return in;
}

bool azheganova::operator==(const Point & first, const Point & second)
{
  return (first.x == second.x) && (first.y == second.y);
}

bool azheganova::operator==(const Polygon & first, const Polygon & second)
{
  auto firstBegin = first.points.begin();
  auto firstEnd = first.points.end();
  auto secondBegin = second.points.begin();
  bool checkEqual = std::equal(firstBegin, firstEnd, secondBegin);
  return first.points.size() == second.points.size() && checkEqual;
}


