#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <cstddef>
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
    Polygon& operator=(const Polygon& other);
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
    struct IsEvenVertexCount
    {
      bool operator()(const Polygon &p) const
      {
        return p.getPointsCount() % 2 == 0;
      }
    };
    struct IsOddVertexCount
    {
      bool operator()(const Polygon &p) const
      {
        return p.getPointsCount() % 2 != 0;
      }
    };
    struct HasVertexCount
    {
      explicit HasVertexCount(size_t vertexCount):
        vertexCount_(vertexCount)
      {
      }
      bool operator()(const Polygon &p) const
      {
        return p.getPointsCount() == vertexCount_;
      }
    private:
      size_t vertexCount_;
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
  private:
    std::vector< Point > points_;
  };
}
#endif
