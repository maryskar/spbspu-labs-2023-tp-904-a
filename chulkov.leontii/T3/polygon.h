#ifndef POLYGON_H
#define POLYGON_H
#include <iosfwd>
#include <vector>

namespace chulkov {
  struct Point {
    int x;
    int y;
  };

  struct Polygon {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& dest);
  std::ostream& operator<<(std::ostream& out, const Point& point);
  std::ostream& operator<<(std::ostream& out, const Polygon& dest);
  bool operator==(const Point& frs, const Point& sec);
  bool operator==(const Polygon& frs, const Polygon& sec);
  bool operator!=(const Point& frs, const Point& sec);
}

#endif
