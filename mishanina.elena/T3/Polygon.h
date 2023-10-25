#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <istream>
#include <iterator>
#include <algorithm>
#include <iotypes.h>
namespace mishanina
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream &operator>>(std::istream &in, Point &point);
  std::istream &operator>>(std::istream &in, Polygon &data);
  bool operator==(const Point &left, const Point &right);
}
#endif
