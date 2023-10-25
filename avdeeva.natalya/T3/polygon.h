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
  std::istream & operator>>(std::istream & in, Point & rhs);
  std::istream & operator>>(std::istream & in, Polygon & rhs);
  bool operator==(const Point & lhs, const Point & rhs);
  bool operator==(const Polygon & lhs, const Polygon & rhs);
  double areaCounter(const Point & lhs, const Point & rhs);
  double getArea(const Polygon & pol);
}
#endif
