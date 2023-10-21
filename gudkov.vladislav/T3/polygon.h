#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <iostream>

namespace gudkov
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

  double getSide(const Point &a, const Point &b);
  double getTriangleArea(const Point &a, const Point &b, const Point &c);
  bool isSecond(const Point &point);
  double getTriangleAreaForArrayOnly(const Point &point);
  double getArea(const Polygon &polygon);
}
#endif
