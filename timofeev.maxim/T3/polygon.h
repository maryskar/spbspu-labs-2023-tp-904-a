#ifndef POLYGON_H
#define POLYGON_H
#include <iostream>
#include <vector>
namespace timofeev
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream &operator>>(std::istream &in, Polygon &dest);
  std::istream &operator>>(std::istream &in, Point &dest);
  size_t size(const Polygon &dest);
}
#endif
