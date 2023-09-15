#ifndef SPBSPU_LABS_2023_TP_904_A_POLYGON_H
#define SPBSPU_LABS_2023_TP_904_A_POLYGON_H
#include <vector>
#include <iostream>
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
  std::istream & operator>>(std::istream & in, const Point & rhs);
  std::istream & operator>>(std::istream & in, const Polygon & rhs);
  size_t size(const Polygon & pol);
  double areaCounter(const Point & lhs, const Point & rhs);
  double getArea(const Polygon & pol);
}
#endif
