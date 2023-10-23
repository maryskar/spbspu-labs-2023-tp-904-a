#ifndef POLYGON_H
#define POLYGON_H
#include <iostream>
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
}

#endif
