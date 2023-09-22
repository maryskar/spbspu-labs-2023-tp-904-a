#include "Polygon.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <IOStructs.hpp>
namespace malaya
{
  bool operator==(const Point & left, const Point & right)
  {
    return (left.x == right.x && left.y == right.y);
  }
  std::istream & operator>>(std::istream & in, Point & point)
  {
    std::istream::sentry istreamChecker(in);
    if (!istreamChecker)
    {
      return in;
    }
    in >> DelimiterIO{'('};
    in >> point.x;
    in >> DelimiterIO{';'};
    in >> point.y;
    in >> DelimiterIO{')'};
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
    if (pointNumber < 3)
    {
      in.setstate(std::ios::failbit);
    }
    std::copy_n(inIter(in), pointNumber, std::back_inserter(polygon.points));
    return in;
  }
  double areaCounter::operator()(const Point & left, const Point & right)
  {
    return 0.5 * (left.x * right.y - right.x * left.y);
  }
  double getArea(const Polygon & polygon)
  {
    double res = 0.0;
    size_t size = polygon.points.size();
    std::vector< double > values(size);
    auto endIt = polygon.points.end();
    std::transform(polygon.points.begin(), --endIt, ++polygon.points.begin(), values.begin(), areaCounter{});
    res = std::accumulate(values.begin(), values.end(), 0.0);
    int x1 = polygon.points.back().x;
    int x2 = polygon.points.front().x;
    int y1 = polygon.points.back().y;
    int y2 = polygon.points.front().y;
    res += 0.5 * (x1 * y2 - y1 * x2);
    return std::abs(res);
  }
}
