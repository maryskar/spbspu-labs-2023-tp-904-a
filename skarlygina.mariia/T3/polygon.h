#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <ios>

namespace skarlygina
{
  struct Point
  {
    size_t x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream&, Point&);
  std::istream& operator>>(std::istream&, Polygon&);
  std::ostream& operator<<(std::ostream&, const Point&);
  std::ostream& operator<<(std::ostream&, const Polygon&);
}


#endif
