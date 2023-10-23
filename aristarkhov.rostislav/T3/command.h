#ifndef COMMAND_H
#define COMMAND_H

#include "polygon.h"
#include <vector>

namespace aristarkhov
{
  size_t getVerticesCount(const Polygon& polygon);
  double getArea(const Polygon& polygon);

  void areaEven(const std::vector< Polygon >& polygons, std::ostream& ostream);
  void areaOdd(const std::vector< Polygon >& polygons, std::ostream& ostream);

}

#endif
