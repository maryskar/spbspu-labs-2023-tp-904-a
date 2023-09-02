#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <cstddef>
#include <vector>
#include <istream>

namespace hrushchev
{
  struct Point
  {
    long long x_;
    long long y_;
  };

  struct Polygon
  {
    std::vector< Point > points_;
  };

  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
}

#endif
