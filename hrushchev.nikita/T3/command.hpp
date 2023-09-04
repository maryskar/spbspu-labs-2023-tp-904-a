#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <ostream>
#include "polygon.hpp"

namespace hrushchev
{
  double calcArea(const Point & left, const Point & right);
  double getArea(const Polygon& polygon);

  void printAreaEven(std::ostream& out, const std::vector< Polygon >& polygons);
}

#endif
