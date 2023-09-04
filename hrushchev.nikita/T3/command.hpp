#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include "polygon.hpp"

namespace hrushchev
{
  double calcArea(const Point & left, const Point & right);
  double getArea(const Polygon& polygon);

  double getAreaEven(const std::vector< Polygon >& polygons);
}

#endif
