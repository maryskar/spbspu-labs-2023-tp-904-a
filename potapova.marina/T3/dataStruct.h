#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <vector>
#include <iostream>
#include <limits>

namespace potapova
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  struct DelimiterIO
  {
    char sign;
  };

  struct Rectangle
  {
    int max_x;
    int min_x;
    int max_y;
    int min_y;

    Rectangle():
      max_x(std::numeric_limits< int >::max()),
      min_x(std::numeric_limits< int >::lowest()),
      max_y(std::numeric_limits< int >::max()),
      min_y(std::numeric_limits< int >::lowest())
    {

    }
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, Point& dest);
  std::ostream& operator<<(std::ostream& out, const Point& source);
  std::istream& operator>>(std::istream& in, Polygon& dest);
  std::ostream& operator<<(std::ostream& out, Polygon& source);
}

#endif
