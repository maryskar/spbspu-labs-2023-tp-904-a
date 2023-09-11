#ifndef GEOMFIGURES_HPP
#define GEOMFIGURES_HPP
#include <iomanip>
#include <vector>
namespace kotova
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
