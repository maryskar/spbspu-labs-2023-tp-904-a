#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <cstddef>
#include <vector>
#include <istream>

namespace hrushchev
{
  struct Point
  {
    size_t x_;
    size_t y_;
  };
  
  struct Polygon
  {
    std::vector< Point > points_;
  };

  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
}

#endif
