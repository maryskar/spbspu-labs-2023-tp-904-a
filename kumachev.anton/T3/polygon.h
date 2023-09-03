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
  };

  size_t getVerticesCount(const Polygon &polygon);
  double getArea(const Polygon &polygon);

  struct PolygonComparator {
    bool operator ()(const Polygon &lhs, const Polygon &rhs);
  };
}

#endif
