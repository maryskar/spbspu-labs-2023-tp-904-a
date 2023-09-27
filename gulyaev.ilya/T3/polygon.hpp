#ifndef T3_POLYGON_HPP
#define T3_POLYGON_HPP
#include <vector>
#include <iostream>

namespace gulyaev
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream &operator>>(std::istream &in, Point &dest);
  std::istream &operator>>(std::istream &in, Polygon &dest);
  bool operator==(const Point &lhs,const Point &rhs);
  std::size_t getSize(const Polygon &pol);
  double getArea(const Polygon &pol);
  bool checkPermutation(const Polygon &lhs, const Polygon &rhs);
  bool checkRightShape(const Polygon &pol);
}
#endif
