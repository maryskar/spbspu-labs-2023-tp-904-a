#ifndef T3_POLYGON_HPP
#define T3_POLYGON_HPP
#include <vector>
#include <iosfwd>

namespace chemodurov
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > data;
  };

  std::istream & operator>>(std::istream & in, Point & dest);
  std::istream & operator>>(std::istream & in, Polygon & dest);
}

#endif
