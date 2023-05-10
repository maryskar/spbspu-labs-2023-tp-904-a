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
  double getPolygonArea(const Polygon& polygon);
  bool isInFrame(const Polygon& fig, const std::vector< Polygon >& polygons);
  size_t countSame(const Polygon& fig, const std::vector< Polygon >& polygons);
  size_t getNumOfVertexes(const Polygon& fig);

}
#endif
