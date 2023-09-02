#include "command.hpp"
#include "polygon.hpp"
#include <cmath>

double hrushchev::triangleArea(const Point& p1, const Point& p2, const Point& p3)
{
  return 0.5 * std::abs((p1.x_ - p3.x_) * (p2.y_ - p3.y_) - (p2.x_ - p3.x_) * (p1.y_ - p3.y_));
}

double hrushchev::getArea(const Polygon& polygon)
{
  double area = 0.0;
  size_t numPoints = polygon.points_.size();

  Point first = polygon.points_[0];
  for (size_t i = 1; i < numPoints - 1; ++i)
  {
    Point second = polygon.points_[i];
    Point third = polygon.points_[i + 1];
    area += triangleArea(first, second, third);
  }

  return area;
}