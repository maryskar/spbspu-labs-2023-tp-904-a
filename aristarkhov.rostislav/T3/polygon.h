#ifndef POLYGON_H
#define POLYGON_H

#include <istream>
#include <vector>

namespace aristarkhov
{
  struct Point
  {
    int x;
    int y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& dest);

  bool operator==(const Point& lhs, const Point& rhs);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
}

#endif
