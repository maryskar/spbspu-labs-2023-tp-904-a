#ifndef T3_SOLVINGCOMMANDS_H
#define T3_SOLVINGCOMMANDS_H
#include "polygon.h"
#include <vector>

namespace mashkin
{
  using iter = std::vector< Polygon >::iterator;
  struct XMultiY
  {
    XMultiY();
    XMultiY(int&& rhs);
    XMultiY(const Point& first, const Point& second);
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

  std::ostream& operator<<(std::ostream& out, const FullArea& data);

  XMultiY solveXY(const Point& lhs, const Point& rhs);
  PositiveArea calcPositiveArea(const Polygon& lhs);
  NegativeArea calcNegativeArea(const Polygon& lhs);
  FullArea solveArea(const PositiveArea& first, const NegativeArea& second);
  std::vector< FullArea > getFullArea(const iter& begin, const iter& end);
  bool isOdd(const Polygon& data);
  bool isEven(const Polygon& data);
}
#endif
