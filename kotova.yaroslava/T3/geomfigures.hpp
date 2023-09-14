#ifndef GEOMFIGURES_HPP
#define GEOMFIGURES_HPP
#include <iomanip>
#include <vector>
#include <iostream>
namespace kotova
{
  struct DelimiterIO
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
  std::istream &operator>>(std::istream &in, Polygon &rhs);
  std::istream &operator>>(std::istream &in, Point &point);
  std::ostream &operator<<(std::ostream &out, const Polygon &rhs);
  std::ostream &operator<<(std::ostream &out, const Point &rhs);
}
#endif
