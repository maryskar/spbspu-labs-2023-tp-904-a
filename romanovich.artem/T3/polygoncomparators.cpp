#include "polygoncomparators.h"
#include <algorithm>
namespace romanovich
{
  bool AreaComp::operator()(const Polygon &lhs, const Polygon &rhs) const
  {
    return lhs.getArea() < rhs.getArea();
  }
  bool PointsCountComp::operator()(const Polygon &lhs, const Polygon &rhs) const
  {
    return lhs.getPointsCount() < rhs.getPointsCount();
  }
  bool IsEvenPointsCount::operator()(const Polygon &p) const
  {
    return p.getPointsCount() % 2 == 0;
  }
  bool IsOddPointsCount::operator()(const Polygon &p) const
  {
    return p.getPointsCount() % 2 != 0;
  }
  bool HasPointsCount::operator()(const Polygon &p) const
  {
    return p.getPointsCount() == pointsCount;
  }
  bool HasNotPointsCount::operator()(const Polygon &p) const
  {
    return p.getPointsCount() != pointsCount;
  }
  bool PolygonComparator::operator()(const Polygon &a, const Polygon &b) const
  {
    return a == b && a == polygon;
  }
  bool IsRightAngle::operator()(const Point &point) const
  {
    size_t n = polygon.getPointsCount();
    auto it = std::find(polygon.begin(), polygon.end(), point);
    auto index = std::distance(polygon.begin(), it);
    const auto &pointA = point;
    const auto &pointB = polygon.getPoint((index + 1) % n);
    const auto &pointC = polygon.getPoint((index + 2) % n);
    const auto v1 = pointB - pointA;
    const auto v2 = pointC - pointB;
    return doScalarMultiplication(v1, v2) == 0;
  }
  bool HasRightAngle::operator()(const Polygon &polygon) const
  {
    return std::any_of(polygon.begin(), polygon.end(), IsRightAngle{polygon});
  }
}
