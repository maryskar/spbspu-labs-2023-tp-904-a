#ifndef TLABSNEW_POLYGON_H
#define TLABSNEW_POLYGON_H
#include <iosfwd>
#include <vector>
namespace timofeev
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
