#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <iterator>
#include <algorithm>
#include <istream>
#include <DataStruct.h>

namespace aksenov
{
  struct Point
  {
    int x, y;
  };

  bool operator==(const Point& lhs, const Point& rhs);

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream & operator>>(std::istream & in, Point & rhs);

  std::istream & operator>>(std::istream & in, Polygon & rhs);
}
#endif
