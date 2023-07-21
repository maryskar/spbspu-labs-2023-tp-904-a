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

  size_t vertex(const Polygon &polygon);
  double getArea(const Polygon &polygon);

  struct PointComparator {
    bool operator ()(const Point &lhs, const Point &rhs);
  };

  struct PolygonComparator {
    bool operator ()(const Polygon &lhs, const Polygon &rhs);
  };
}

#endif
