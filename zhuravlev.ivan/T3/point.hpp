#ifndef POINT_HPP
#define POINT_HPP
#include <vector>
#include <iostream>
#include "common/IO_separators.hpp"
#include "common/iofmtguard.hpp"

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
