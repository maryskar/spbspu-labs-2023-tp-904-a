#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <vector>
#include <iomanip>

namespace azheganova
{
  struct DelimiterIO
  {
    char exp;
  };
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };

  double getArea(const Polygon & polygon);
  double getTriangleArea(const Point & point1, const Point & point2);
  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  std::istream & operator>>(std::istream & in, Point & dest);
  std::istream & operator>>(std::istream & in, Polygon & dest);
}

#endif
