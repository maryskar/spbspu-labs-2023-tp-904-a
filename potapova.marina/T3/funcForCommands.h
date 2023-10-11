#ifndef FUNCFORCOMMANDS_H
#define FUNCFORCOMMANDS_H

#include "dataStruct.h"

namespace potapova
{
  double getPolygonArea(const Polygon& polygon);
  template< size_t ParityFlag >
  double getSumPolygonsAreasT(const std::deque< Polygon >& polygons);
  double getSumPolygonsAreas(const std::deque< Polygon >& polygons);
  size_t countPolygons(const std::deque< Polygon >& polygons);
  bool checkDesiredNumPoints(size_t num_points, const Polygon& polygon);
  double addAreaToSumIfNumPoints(double sum, const Polygon& polygon, size_t num_points);
  bool comparePolygonsAreas(const Polygon& first, const Polygon& second);
  bool comparePolygonsPoints(const Polygon& first, const Polygon& second);
  bool isOddPointNum(const Polygon& polygon);
  bool isEvenPointNum(const Polygon& polygon);
  bool comparePolygonsEqual(const Polygon& first, const Polygon& second, const Polygon& target_polygon);
  bool isInFrame(const Rectangle& frame, const Polygon& polygon);
}

#endif
