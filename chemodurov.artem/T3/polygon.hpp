#ifndef T3_POLYGON_HPP
#define T3_POLYGON_HPP
#include <vector>

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
}

#endif
