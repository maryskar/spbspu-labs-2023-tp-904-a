#ifndef POLYGON_H
#define POLYGON_H
#include <iostream>
#include <vector>
#include "point.h"
namespace fesenko
{
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream &operator>>(std::istream &in, Polygon &rhs);
  std::ostream &operator<<(std::ostream &out, const Polygon &rhs);
}
#endif
