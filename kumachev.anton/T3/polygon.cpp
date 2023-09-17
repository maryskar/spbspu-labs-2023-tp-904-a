#include "polygon.h"
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>

namespace kumachev {
  static double getTriangleArea(const Point &p1, const Point &p2)
  {
    return p1.x * p2.y - p1.y * p2.x;
  }

  size_t getVerticesCount(const Polygon &polygon)
  {
    return polygon.points.size();
  }

  double getArea(const Polygon &polygon)
  {
    using namespace std::placeholders;
    auto areaOperator = std::bind(getTriangleArea, _2, _1);

    std::vector< double > values;
    values.reserve(getVerticesCount(polygon));
    auto inserter = std::back_inserter(values);

    auto first = polygon.points.begin();
    auto second = first;
    ++second;
    auto end = polygon.points.end();

    std::transform(second, end, first, inserter, areaOperator);
    double area = std::accumulate(values.begin(), values.end(), .0);
    area += areaOperator(polygon.points.front(), polygon.points.back());
    area = std::abs(area) / 2;

    return area;
  }

  bool Point::operator==(const Point &other) const
  {
    return x == other.x && y == other.y;
  }

  bool Polygon::operator==(const Polygon &other) const
  {
    if (points.size() != other.points.size()) {
      return false;
    }

    auto leftBegin = points.begin();
    auto leftEnd = points.end();
    auto rightBegin = other.points.begin();

    return std::equal(leftBegin, leftEnd, rightBegin);
  }
}
