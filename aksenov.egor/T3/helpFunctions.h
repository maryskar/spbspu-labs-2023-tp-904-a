#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H
#include <vector>
#include <string>
#include "polygon.h"

namespace aksenov
{
  std::vector< double > getArea(const std::vector< Polygon > &pol);
  bool isOdd(const Polygon& data);
  bool isEven(const Polygon& data);
  bool isInteger(const std::string & s);
  bool isNotEqual(const Polygon &pol, size_t num);
  bool isEqual(const Polygon &pol, size_t amount);
  bool comparePoints(const Point &lhs, const Point &rhs);
  Point translatePoint(const Point& point, int diffX, int diffY);
  bool isSame(const Polygon& lhs, const Polygon& rhs);

}
#endif
