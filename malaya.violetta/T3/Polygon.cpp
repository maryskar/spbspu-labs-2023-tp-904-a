#include "Polygon.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <numeric>

namespace malaya
{
  std::istream & operator>>(std::istream & in, SeparatorPointIO && separator)
  {
    std::istream::sentry istreamChecker(in);
    if (!istreamChecker)
    {
      return in;
    }
    char input = '0';
    in >> input;
    if (in && (input != separator.sep))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  bool operator==(const Point & left, const Point & right)
  {
    return (left.x == right.x && left.y == right.y);
  }

  bool PointComparator::operator()(const Point & left, const Point & right)
  {
    if(left.x != right.x)
    {
      return left.x < right.x;
    }
    else
    {
      return left.y < right.y;
    }
  }


  std::istream & operator>>(std::istream & in, Point & point)
  {
    std::istream::sentry istreamChecker(in);
    if (!istreamChecker)
    {
      return in;
    }
    in >> SeparatorPointIO{'('};
    in >> point.x;
    in >> SeparatorPointIO{';'};
    in >> point.y;
    in >> SeparatorPointIO{')'};
    return in;
  }

  std::istream & operator>>(std::istream & in, Polygon & polygon)
  {
    std::istream::sentry istreamChecker(in);
    if (!istreamChecker)
    {
      return in;
    }
    polygon.points.clear();
    using inIter = std::istream_iterator< Point >;
    int pointNumber = 0;
    in >> pointNumber;
    std::copy_n(inIter(in), pointNumber, std::back_inserter(polygon.points));
    return in;
  }

  double areaCounter::operator()(const Point & left, const Point & right)
  {
    return (0.5 * (left.x * right.y - right.x * left.y));
  }
  double getArea(const Polygon & polygon)
  {
    double result = 0.0;
    size_t size = polygon.points.size();
    std::vector< double > values;
    std::transform(polygon.points.begin(), --polygon.points.end(),
                   ++polygon.points.begin(), values.begin(),
                   areaCounter{});
    result = std::accumulate(values.begin(), values.end(), 0.0);
    result += 0.5 * (polygon.points[size - 1].x * polygon.points[0].y -
                     polygon.points[size - 1].y * polygon.points[0].x);
    return std::abs(result);
  }
}