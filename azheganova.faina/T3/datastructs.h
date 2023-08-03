#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <vector>

namespace azheganova
{
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
}

#endif
