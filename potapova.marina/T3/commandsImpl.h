#ifndef COMMANDSIMPL_H
#define COMMANDSIMPL_H

#include <cstdio>
#include <numeric>
#include <deque>
#include "dataStructs.h"
#include "rectangle.h"

namespace potapova
{
  enum class ParityFlags
  {
    EVEN = 0,
    ODD = 1
  };

  double getArea(const Polygon& polygon);
  double addAreaToSum(const double sum, const potapova::Polygon& polygon);
  double getSumOfAreas(const std::deque< Polygon >& polygons);
  bool checkDesiredNumPoints(size_t num_points, const potapova::Polygon& polygon) noexcept;
  double addAreaToSumIfNumPoints(double sum, const Polygon& polygon, size_t num_points);
  bool comparePolygonsAreas(const Polygon& first, const Polygon& second);
  bool comparePolygonsPoints(const Polygon& first, const Polygon& second);
  bool isEqual(const Polygon& first, const Polygon& second, const Polygon& target_polygon) noexcept;

  template< ParityFlags ParityFlag >
  double addSpecificAreaToSum(const double sum, const potapova::Polygon& polygon)
  {
    if ((polygon.points.size() & 1) == static_cast< size_t >(ParityFlag))
    {
      return addAreaToSum(sum, polygon);
    }
    return sum;
  }

  template< ParityFlags ParityFlag >
  double getSumOfSpecificAreas(const std::deque< Polygon >& polygons)
  {
    double area = std::accumulate(polygons.begin(), polygons.end(), 0.0, addSpecificAreaToSum< ParityFlag >);
    return area;
  }

  template< ParityFlags ParityFlag >
  bool isSpecificPointsNum(const Polygon& polygon) noexcept
  {
    return (polygon.points.size() & 1) == static_cast< size_t >(ParityFlag);
  }
}

#endif
