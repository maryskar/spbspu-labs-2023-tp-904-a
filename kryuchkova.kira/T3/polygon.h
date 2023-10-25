#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include "point.h"

namespace kryuchkova
{
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream & operator>>( std::istream & in, Polygon & polygon);
  double getArea(const Polygon & polygon);
}

#endif
