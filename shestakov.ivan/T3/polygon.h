#ifndef UNTITLED3_POLYGON_H
#define UNTITLED3_POLYGON_H
#include <iostream>
#include <vector>

namespace shestakov
{
  struct DelimeterIO
  {
    char exp;
  };
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  bool operator ==(const Point &lhs, const Point &rhs);
  bool operator ==(const Polygon &lhs, const Polygon &rhs);
  std::istream & operator>>(std::istream & in, DelimeterIO &&dest);
  std::istream & operator>>(std::istream & in, Point & rhs);
  std::istream & operator>>(std::istream & in, Polygon & rhs);
}
#endif
