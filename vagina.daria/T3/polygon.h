#ifndef T3_POLYGON_H
#define T3_POLYGON_H
#include <vector>
#include <iomanip>

namespace vagina
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  bool comparatorArea(const Polygon& lhs, const Polygon& rhs);
  bool comparatorVertexes(const Polygon& lhs, const Polygon& rhs);
  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
  double getArea(const Polygon& dest);
}


#endif
