#ifndef POLYGONCOMPARATORS_H
#define POLYGONCOMPARATORS_H
#include "polygon.h"
namespace romanovich
{
  struct AreaComp
  {
    bool operator()(const Polygon &lhs, const Polygon &rhs) const;
  };
  struct AreaFunctor
  {
    double operator()(const romanovich::Polygon &polygon) const;
  };
  struct PointsCountComp
  {
    bool operator()(const Polygon &lhs, const Polygon &rhs) const;
  };
  struct IsEvenPointsCount
  {
    bool operator()(const Polygon &p) const;
  };
  struct IsOddPointsCount
  {
    bool operator()(const Polygon &p) const;
  };
  struct HasPointsCount
  {
    explicit HasPointsCount(size_t pointsCount):
      pointsCount(pointsCount)
    {
    }
    bool operator()(const Polygon &p) const;
  private:
    size_t pointsCount;
  };
  struct HasNotPointsCount
  {
    explicit HasNotPointsCount(size_t pointsCount):
      pointsCount(pointsCount)
    {
    }
    bool operator()(const Polygon &p) const;
  private:
    size_t pointsCount;
  };
  struct PolygonComparator
  {
    explicit PolygonComparator(const Polygon &polygon):
      polygon(polygon)
    {
    }
    bool operator()(const Polygon &a, const Polygon &b) const;
    const Polygon &polygon;
  };
  struct IsRightAngle
  {
    const Polygon &polygon;
    bool operator()(const Point &point) const;
  };
  struct HasRightAngle
  {
    bool operator()(const Polygon &polygon) const;
  };
}
#endif
