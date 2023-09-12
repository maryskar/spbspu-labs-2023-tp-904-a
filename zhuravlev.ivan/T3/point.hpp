#ifndef POINT_HPP
#define POINT_HPP
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
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
  std::istream& operator>>(std::istream& in, Polygon rhs);
}
#endif
