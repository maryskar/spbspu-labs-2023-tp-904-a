#ifndef EXTRA_COMMANDS_H
#define EXTRA_COMMANDS_H
#include "Polygon.h"
#include <numeric>
namespace mishanina{
  bool isEven(const Polygon& polygon);
  bool isOdd(const Polygon& polygon);
  double getSide(const Point& p1, const Point& p2);
  double getArea(const Polygon& polygon);
  template <class P>
  std::vector<Polygon> getPolygonsIf(const std::vector<Polygon> &polygons, P p)
  {
    std::vector<Polygon> polygonsIf;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(polygonsIf), p);
    return polygonsIf;
  }
  template <class P>
  double getAreaIf(const std::vector<Polygon> &polygons, P p)
  {
    std::vector<Polygon> polygonsIf = getPolygonsIf(polygons, p);
    std::vector<double> areas(polygonsIf.size());
    std::transform(polygonsIf.begin(), polygonsIf.end(), areas.begin(), getArea);
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
    return sum;
  }
}

#endif
