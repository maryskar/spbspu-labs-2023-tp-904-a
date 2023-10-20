#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <vector>

namespace tarasenko
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::ostream& operator<<(std::ostream& out, const Point& src);
  std::istream& operator>>(std::istream& in, Point& dest);
  std::ostream& operator<<(std::ostream& out, const Polygon& src);
  std::istream& operator>>(std::istream& in, Polygon& dest);
}
#endif
