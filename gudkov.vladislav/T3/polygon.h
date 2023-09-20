#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <iostream>

namespace gudkov
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream &operator>>(std::istream &in, Point &dest);
  std::ostream &operator<<(std::ostream &out, const Point &dest);

  std::istream &operator>>(std::istream &in, Polygon &dest);
  std::ostream &operator<<(std::ostream &out, const Polygon &dest);
}
#endif
