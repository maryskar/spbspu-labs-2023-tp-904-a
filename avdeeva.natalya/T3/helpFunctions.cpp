#include "helpFunctions.h"
bool avdeeva::isOdd(const Polygon & pol)
{
  return (size(pol) % 2);
}
bool avdeeva::isEven(const Polygon & pol)
{
  return !(isOdd(pol));
}
bool avdeeva::isNumOfVerts(const Polygon & pol, size_t num)
{
  return size(pol) == num;
}
bool avdeeva::compArea(const Polygon & lhs, const Polygon & rhs)
{
  return (getArea(lhs) < getArea(rhs));
}
bool avdeeva::compSize(const Polygon & lhs, const Polygon & rhs)
{
  return (lhs.points.size() < rhs.points.size());
}
double avdeeva::getDist(const Point & lhs, const Point & rhs)
{
  return std::sqrt(std::pow(std::abs(lhs.x - rhs.x), 2) + std::pow(std::abs(lhs.y - rhs.y), 2));
}