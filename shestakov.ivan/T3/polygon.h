#ifndef UNTITLED3_POLYGON_H
#define UNTITLED3_POLYGON_H
#include <iostream>
#include <vector>
#include <TypesIO.h>

namespace shestakov
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  bool operator==(const Point& lhs, const Point& rhs);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
  std::istream& operator>>(std::istream& in, Point& rhs);
  std::istream& operator>>(std::istream& in, Polygon& rhs);
}
#endif
