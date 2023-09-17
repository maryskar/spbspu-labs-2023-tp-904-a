#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <istream>

namespace mishanina
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector<Point> points;
  };
  std::istream &operator>>(std::istream &in, Point &&data);
  std::istream &operator>>(std::istream &in, Polygon &&data);
  std::ostream &operator<<(std::ostream &out, const Point &data);
  std::ostream &operator<<(std::ostream &out, const Polygon &data);
}
#endif
