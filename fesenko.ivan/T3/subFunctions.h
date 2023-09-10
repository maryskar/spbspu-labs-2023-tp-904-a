#ifndef CALCAREA_H
#define CALCAREA_H
#include "polygon.h"
namespace fesenko
{
  double calcArea(double in, const Polygon &rhs);
  bool isOdd(const Polygon &rhs);
  bool isEven(const Polygon &rhs);
}
#endif
