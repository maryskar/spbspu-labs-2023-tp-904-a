#ifndef SPBSPU_LABS_2023_TP_904_A_POLYGON_H
#define SPBSPU_LABS_2023_TP_904_A_POLYGON_H
#include <vector>
namespace avdeeva
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
