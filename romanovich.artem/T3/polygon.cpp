#include "polygon.h"
size_t Polygon::getPointsCount() const
{
  return points_.size();
}
Point Polygon::getPoint(size_t index) const
{
  return points_[index];
}
Polygon::Polygon(const std::vector< Point > &points):
  points_(points)
{
}
double Polygon::getArea() const
{
  double area = 0.0;
  size_t n = getPointsCount();
  if (n >= 3)
  {
    size_t j = n - 1;
    for (int i = 0; i < n; i++)
    {
      area += (getPoint(j).x + getPoint(i).x) * (getPoint(j).y - getPoint(i).y);
      j = i;
    }
    return std::abs(area / 2.0);
  }
  return 0;
}
bool Polygon::operator==(const Polygon &rhs) const
{
  if (getPointsCount() != rhs.getPointsCount())
  {
    return false;
  }
  for (size_t i = 0; i < rhs.getPointsCount(); ++i)
  {
    if (getPoint(i) != rhs.getPoint(i))
    {
      return false;
    }
  }
  return true;
}
