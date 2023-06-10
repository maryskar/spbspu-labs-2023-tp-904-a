#ifndef T3_POLYGON_H
#define T3_POLYGON_H
#include <vector>
#include <iomanip>

namespace vagina
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
}


#endif
