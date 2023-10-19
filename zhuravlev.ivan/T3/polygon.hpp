#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include <iostream>
#include <IO_separators.hpp>
#include <iofmtguard.hpp>

namespace zhuravlev
{
  struct Point
  {
    int x;
    int y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Point& rhs);
  std::ostream& operator<<(std::ostream& out, const Point& rhs);
  std::istream& operator>>(std::istream& in, Polygon& rhs);
  std::ostream& operator<<(std::ostream& out, const Polygon& rhs);
  bool operator==(const Point& lhs, const Point& rhs);
}
#endif
