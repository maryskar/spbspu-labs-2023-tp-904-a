#ifndef T3_POLYGON_HPP
#define T3_POLYGON_HPP
#include <iosfwd>
#include <vector>
namespace litvin
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
}
#endif
