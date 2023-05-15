#include "getArea.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
#include "Polygon.hpp"

namespace malaya
{
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
    result = std::accumulate(values.begin(), values.end(), 0.0, std::plus<>{}); //????
    result += 0.5 * (polygon.points[size - 1].x * polygon.points[0].y -
      polygon.points[size - 1].y * polygon.points[0].x);
    return std::abs(result);
  }
}