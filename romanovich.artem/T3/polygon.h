#ifndef POLYGON_H
#define POLYGON_H
#include <cstddef>
#include <vector>
#include <algorithm>
#include "point.h"
namespace romanovich
{
  class Polygon
  {
  public:
    explicit Polygon(const std::vector< Point > &points);
    size_t getPointsCount() const;
    Point getPoint(size_t index) const;
    double getArea() const;
    bool operator==(const Polygon &rhs) const;
    auto begin() const
    {
      return points_.begin();
    }
    auto end() const
    {
      return points_.end();
    }
    struct AreaComp
    {
      bool operator()(const Polygon &lhs, const Polygon &rhs) const
      {
        return lhs.getArea() < rhs.getArea();
      }
    };
    struct AreaFunctor
    {
      double operator()(const romanovich::Polygon &polygon) const
      {
        return polygon.getArea();
      }
    };
    struct PointsCountComp
    {
      bool operator()(const Polygon &lhs, const Polygon &rhs) const
      {
        return lhs.getPointsCount() < rhs.getPointsCount();
      }
    };
    struct IsEvenPointsCount
    {
      bool operator()(const Polygon &p) const
      {
        return p.getPointsCount() % 2 == 0;
      }
    };
    struct IsOddPointsCount
    {
      bool operator()(const Polygon &p) const
      {
        return p.getPointsCount() % 2 != 0;
      }
    };
    struct HasPointsCount
    {
      explicit HasPointsCount(size_t pointsCount):
        pointsCount(pointsCount)
      {
      }
      bool operator()(const Polygon &p) const
      {
        return p.getPointsCount() == pointsCount;
      }
    private:
      size_t pointsCount;
    };
    struct HasNotPointsCount
    {
      explicit HasNotPointsCount(size_t pointsCount):
        pointsCount(pointsCount)
      {
      }
      bool operator()(const Polygon &p) const
      {
        return p.getPointsCount() != pointsCount;
      }
    private:
      size_t pointsCount;
    };
    struct PolygonComparator
    {
      explicit PolygonComparator(const Polygon &polygon):
        polygon(polygon)
      {
      }
      bool operator()(const Polygon &a, const Polygon &b) const
      {
        return a == b && a == polygon;
      }
      const Polygon &polygon;
    };
    struct IsRightAngle
    {
      const Polygon &polygon;
      bool operator()(const Point &point) const
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
    };
    struct HasRightAngle
    {
      bool operator()(const Polygon &polygon) const
      {
        return std::any_of(polygon.begin(), polygon.end(), IsRightAngle{polygon});
      }
    };
  private:
    std::vector< Point > points_;
  };
}
#endif
