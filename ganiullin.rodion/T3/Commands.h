#ifndef COMMANDS_H
#define COMMANDS_H
#include "Geometry.h"

#include <iosfwd>

namespace ganiullin {
  double processArea(std::istream& in, const std::vector< Polygon >& polygons);
  double processMin(std::istream& in, const std::vector< Polygon >& polygons);
  double processMax(std::istream& in, const std::vector< Polygon >& polygons);
}
#endif
