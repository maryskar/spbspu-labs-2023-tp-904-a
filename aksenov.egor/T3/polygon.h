#ifndef POLYGON_H
#define POLYGON_H
#include <vector>

namespace aksenov
{
  struct Point
  {
    int x, y;
  };

  bool operator==(const Point& lhs, const Point& rhs)
  {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
  }

  struct Polygon
  {
    std::vector< Point > points;
  };
}
#endif
