#ifndef T3_POLYGON_H
#define T3_POLYGON_H

#include <vector>
#include <cstddef>

namespace kumachev {
  struct Point {
    int x;
    int y;

    bool operator == (const Point &other) const;
  };

  struct Polygon {
    std::vector< Point > points;

    bool operator == (const Polygon &other) const;
  };

  size_t getVerticesCount(const Polygon &polygon);
  double getArea(const Polygon &polygon);
}

#endif
