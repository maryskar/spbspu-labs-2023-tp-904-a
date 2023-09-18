#ifndef T3_POLYGON_H
#define T3_POLYGON_H

#include <vector>
#include <cstddef>

namespace kumachev {
  struct Point {
    int x;
    int y;
  };

  struct Polygon {
    std::vector< Point > points;
  };

  bool operator == (const Point& lhs, const Point& rhs);
  bool operator == (const Polygon& lhs, const Polygon& rhs);

  size_t getVerticesCount(const Polygon &polygon);
  double getArea(const Polygon &polygon);
}

#endif
