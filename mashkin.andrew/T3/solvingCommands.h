#ifndef T3_SOLVINGCOMMANDS_H
#define T3_SOLVINGCOMMANDS_H
#include "polygon.h"

namespace mashkin
{
  struct XMultiY
  {
    XMultiY();
    XMultiY(int&& rhs);
    XMultiY(const mashkin::Point& first, const mashkin::Point& second);
    XMultiY operator+(const XMultiY& rhs);
    int res;
  };

  struct PositiveArea
  {
    PositiveArea(const Polygon& lhs);
    std::vector< XMultiY > halfArea;
  };

  struct NegativeArea
  {
    NegativeArea(const Polygon& lhs, const Polygon& rhs);
    std::vector< XMultiY > halfArea;
  };

  struct FullArea
  {
    FullArea(const PositiveArea& first, const NegativeArea& second);
    double res;
  };
  XMultiY solveXY(const Point& lhs, const Point& rhs);
  PositiveArea calcPositiveArea(const Polygon& lhs);
  NegativeArea calcNegativeArea(const Polygon& lhs);
  FullArea solveArea(const PositiveArea& first, const NegativeArea& second);
}
#endif
