#include "polygoncomparators.h"
#include <algorithm>
#include "polygonutils.h"
namespace romanovich
{
  bool AreaComp::operator()(const Polygon &lhs, const Polygon &rhs) const
  {
    return getArea(lhs) < getArea(rhs);
  }
  double AreaFunctor::operator()(const romanovich::Polygon &polygon) const
  {
    return getArea(polygon);
  }
  bool PointsCountComp::operator()(const Polygon &lhs, const Polygon &rhs) const
  {
    return getPointsCount(lhs) < getPointsCount(rhs);
  }
  bool IsEvenPointsCount::operator()(const Polygon &p) const
  {
    return getPointsCount(p) % 2 == 0;
  }
  bool IsOddPointsCount::operator()(const Polygon &p) const
  {
    return getPointsCount(p) % 2 != 0;
  }
  bool HasPointsCount::operator()(const Polygon &p) const
  {
    return getPointsCount(p) == pointsCount;
  }
  bool HasNotPointsCount::operator()(const Polygon &p) const
  {
    return getPointsCount(p) != pointsCount;
  }
  bool PolygonComparator::operator()(const Polygon &a, const Polygon &b) const
  {
    return a == b && a == polygon;
  }
  bool IsRightAngle::operator()(const Point &point) const
  {
    size_t n = getPointsCount(polygon);
    std::vector< Point >::const_iterator it = std::find(begin(polygon), end(polygon), point);
    std::ptrdiff_t index = std::distance(begin(polygon), it);
    const Point &pointA = point;
    const Point &pointB = polygon.points[(index + 1) % n];
    const Point &pointC = polygon.points[(index + 2) % n];
    const Point v1 = pointB - pointA;
    const Point v2 = pointC - pointB;
    return doScalarMultiplication(v1, v2) == 0;
  }
  bool HasRightAngle::operator()(const Polygon &polygon) const
  {
    return std::any_of(begin(polygon), end(polygon), IsRightAngle{polygon});
  }
}
