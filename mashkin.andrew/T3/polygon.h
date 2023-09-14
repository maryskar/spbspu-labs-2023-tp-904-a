#ifndef T3_POLYGON_H
#define T3_POLYGON_H
#include <vector>
#include <iostream>

namespace mashkin
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& inp, Point& point);
  std::istream& operator>>(std::istream& inp, Polygon& dest);

  bool operator<(const Polygon& lhs, const Polygon& rhs);
  bool operator==(const Point& lhs, const Point& rhs);
  bool operator<(const Point& lhs, const Point& rhs);
}
#endif
