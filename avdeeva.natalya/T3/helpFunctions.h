#ifndef SPBSPU_LABS_2023_TP_904_A_HELPFUNCTIONS_H
#define SPBSPU_LABS_2023_TP_904_A_HELPFUNCTIONS_H
#include "polygon.h"
namespace avdeeva
{
  bool isOdd(const Polygon & pol);
  bool isEven(const Polygon & pol);
  bool isNumOfVerts(const Polygon & pol, size_t num);
  bool compArea(const Polygon & lhs, const Polygon & rhs);
  bool compSize(const Polygon & lhs, const Polygon & rhs);
  double getDist(const Point & lhs, const Point & rhs);
  bool isRightTriangle(const Point & lhs, const Point & rhs, const Point & third);
  bool checkTriangle(Point & first, Point & second, const Point & third);
  bool isRightshape(const Polygon & polygon);
  Point minPoint(const Polygon& polygon);
  Point maxPoint(const Polygon& polygon);
  Polygon createFrame(const std::deque< Polygon > & polygons);
}
#endif
