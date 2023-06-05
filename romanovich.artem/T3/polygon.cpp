#include "polygon.h"
size_t romanovich::Polygon::getPointsCount() const
{
  return points_.size();
}
romanovich::Point romanovich::Polygon::getPoint(size_t index) const
{
  return points_.at(index);
}
romanovich::Polygon::Polygon(const std::vector< Point > &points):
  points_(points)
{
}
double romanovich::Polygon::getArea() const
{
  double area = 0.0;
  size_t n = getPointsCount();
  if (n >= 3)
  {
    size_t j = n - 1;
    for (size_t i = 0; i < n; i++)
    {
      area += (getPoint(j).x + getPoint(i).x) * (getPoint(j).y - getPoint(i).y);
      j = i;
    }
    return std::abs(area / 2.0);
  }
  return 0;
}
bool romanovich::Polygon::operator==(const Polygon &rhs) const
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
auto romanovich::Polygon::begin() const
{
  return points_.begin();
}
auto romanovich::Polygon::end() const
{
  return points_.end();
}
