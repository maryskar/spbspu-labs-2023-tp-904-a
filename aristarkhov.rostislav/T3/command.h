#ifndef COMMAND_H
#define COMMAND_H

#include "polygon.h"
#include <vector>

namespace aristarkhov
{
  size_t getVerticesCount(const Polygon& polygon);
  double getArea(const Polygon& polygon);

  void countOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void countEven(const std::vector< Polygon >& polygons, std::ostream& out);

  void areaEven(const std::vector< Polygon >& polygons, std::ostream& ostream);
  void areaOdd(const std::vector< Polygon >& polygons, std::ostream& ostream);
  void areaMean(const std::vector< Polygon >& polygons, std::ostream& ostream);
  void areaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
}

#endif
