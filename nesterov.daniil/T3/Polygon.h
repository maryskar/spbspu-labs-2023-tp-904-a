#ifndef T3_NEW_POLYGON_H
#define T3_NEW_POLYGON_H

#include <iostream>
#include <vector>

namespace nesterov
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream &operator>>(std::istream &in, Point &rhs);
  std::ostream &operator<<(std::ostream &out, const Point &rhs);
  std::istream &operator>>(std::istream &in, Polygon &rhs);
  std::ostream &operator<<(std::ostream &out, const Polygon &rhs);
  bool operator==(const Polygon &lhs, const Polygon &rhs);
  bool operator!=(const Polygon &lhs, const Polygon &rhs);
  bool operator==(const Point &lhs, const Point &rhs);
}

#endif
