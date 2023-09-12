#ifndef GEOMFIGURES_HPP
#define GEOMFIGURES_HPP
#include <iomanip>
#include <vector>
#include <iostream>
namespace kotova
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream &operator>>(std::istream &in, Polygon &rhs);
  std::istream &operator>>(std::istream &in, const Point &rhs);
}
#endif
