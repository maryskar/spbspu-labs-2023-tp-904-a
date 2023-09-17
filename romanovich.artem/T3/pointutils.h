#ifndef POINTUTILS_H
#define POINTUTILS_H
#include "point.h"
#include "polygon.h"
#include <istream>
namespace romanovich
{
  bool operator==(const Point &lhs, const Point &rhs);
  bool operator!=(const Point &lhs, const Point &rhs);
  Point operator-(const Point &lhs, const Point &rhs);
  std::istream &operator>>(std::istream &in, Point &dest);
  double doScalarMultiplication(const Point &v1, const Point &v2);
}
#endif
