#ifndef COMMANDS_H
#define COMMANDS_H
#include "polygon.h"

namespace chulkov {
  void getArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void getMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void getMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void getCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void getPerms(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void getRmecho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
}

#endif
