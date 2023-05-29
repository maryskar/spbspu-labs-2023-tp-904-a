#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <iosfwd>
#include <vector>
namespace ganiullin {
  struct Point {
    int x, y;
  };
  struct Polygon {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Point& point);

  bool operator==(const Point& first, const Point& second);
  double getArea(const Polygon& polygon);
  bool isInFrame(const Polygon& fig, const std::pair< Point, Point >& frame);
  bool isSame(const Polygon& lhs, const Polygon& rhs);
  size_t getNumOfVertexes(const Polygon& fig);
  std::pair< Point, Point > getFrame(const std::vector< Polygon >& polygons);
}
#endif
