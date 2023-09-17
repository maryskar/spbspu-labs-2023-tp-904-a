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
  struct Point{
    int x, y;
  };
  struct Polygon : public std::error_code
  {
    std::vector< Point > points;
  };
  std::istream & operator>>(std::istream & in, DelimeterIO &&dest);
  std::istream & operator>>(std::istream & in, Point & rhs);
  std::istream & operator>>(std::istream & in, Polygon & rhs);
}
#endif
