#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <vector>
#include <iomanip>

namespace azheganova
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream & operator>>(std::istream & in, Point & dest);
  std::istream & operator>>(std::istream & in, Polygon & dest);
  bool operator==(const Point & first, const Point & second);
  bool operator==(const Polygon & first, const Polygon & second);
}

#endif
