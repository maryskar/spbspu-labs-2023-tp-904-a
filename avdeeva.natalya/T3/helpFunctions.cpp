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