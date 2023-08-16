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
    std::istream &operator>>(std::istream &in, Polygon & dest);
    std::istream &operator>>(std::istream &in, Point &dest);
}
#endif

