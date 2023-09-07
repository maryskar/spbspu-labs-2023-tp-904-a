#ifndef POLYGON_H
#define POLYGON_H
#include <vector>

namespace skarlygina
{
  struct Point
  {
    size_t x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };
}

#endif
