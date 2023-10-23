#ifndef POLYGON_H
#define POLYGON_H
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

}

#endif
