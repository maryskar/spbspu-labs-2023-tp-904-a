#include "polygon.h"
size_t Polygon::pointsCount() const
{
  return points_.size();
}
const Point &Polygon::getPoint(size_t index) const
{
  return points_[index];
}
Polygon::Polygon(const std::vector< Point > &points):
  points_(points)
{
}
double Polygon::getArea() const
{
  return 0.0;
}
