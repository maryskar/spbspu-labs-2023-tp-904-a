#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <ios>
#include "point.h"

namespace skarlygina
{
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream&, Polygon&);
  std::ostream& operator<<(std::ostream&, const Polygon&);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
  bool operator!=(const Polygon& lhs, const Polygon& rhs);
}

#endif
