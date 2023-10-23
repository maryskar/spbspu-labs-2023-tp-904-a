#include "commands.h"
#include <cmath>
#include <functional>
#include <vector>
#include <algorithm>

namespace aristarkhov
{
  size_t getVerticesCount(const Polygon& polygon)
  {
    return polygon.points.size();
  }

  static double getTriangleArea(const aristarkhov::Point& lhs, const aristarkhov::Point& rhs)
  {
    return (lhs.x * rhs.y) - (lhs.y * rhs.x);
  }

  double getArea(const Polygon& polygon)
  {
    using namespace std::placeholders;

    std::vector< double > values(polygon.points.size());
    std::transform(polygon.points.begin(), --polygon.points.end(), ++polygon.points.begin(), std::back_inserter(values),
      getTriangleArea);
    values.push_back(getTriangleArea(polygon.points.back(), polygon.points.front()));
    double area = std::accumulate(values.begin(), values.end(), 0.0);
    area = std::abs(area / 2);

    return area;
  }
}
