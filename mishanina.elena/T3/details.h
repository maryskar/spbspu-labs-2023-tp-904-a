#ifndef DETAILS_H
#define DETAILS_H
#include <numeric>
#include <functional>
#include "Polygon.h"
namespace mishanina
{
  bool isEven(const Polygon &polygon);
  bool isOdd(const Polygon &polygon);
  bool isCountOfVertexes(const Polygon &polygon, std::size_t num);
  bool isEqualPolygon(const Polygon &lhs, const Polygon &rhs, const Polygon &polygon);
  std::size_t getNumOfVertexes(const Polygon &polygon);
  double getSide(const Point &p1, const Point &p2);
  double getArea(const Polygon &polygon);
  double getTotalArea(const std::vector< Polygon > &pol);
  std::size_t getMaxMinVert(const std::vector< Polygon > &polygons, bool isMax);
  double getMaxMinArea(const std::vector< Polygon > &polygons, bool isMax);
  std::vector< Polygon > getPolygonsWithNumOfVertexes(const std::vector< Polygon > &polygons, std::size_t num);
  double getSideF(const Point &p1, const Point &p2);
  bool isParallelorgam(double side1, double side2, double side3, double side4);
  bool isRectangle(const Polygon &polygon);
  template< class P >
  std::vector< Polygon > getPolygonsIf(const std::vector< Polygon > &polygons, P p)
  {
    std::vector< Polygon > polygonsIf;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(polygonsIf), p);
    return polygonsIf;
  }
  template< class P >
  double getAreaIf(const std::vector< Polygon > &polygons, P p)
  {
    std::vector< Polygon > polygonsIf = getPolygonsIf(polygons, p);
    std::vector< double > areas(polygonsIf.size());
    std::transform(polygonsIf.begin(), polygonsIf.end(), areas.begin(), getArea);
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
    return sum;
  }
  template< class P >
  std::size_t getCountIf(const std::vector< Polygon > &polygons, P p)
  {
    std::vector< Polygon > polygonsIf = getPolygonsIf(polygons, p);
    std::size_t res = std::count_if(polygonsIf.begin(), polygonsIf.end(), p);
    return res;
  }
}
#endif
