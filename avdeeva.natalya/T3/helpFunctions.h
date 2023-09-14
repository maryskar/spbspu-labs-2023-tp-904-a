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
}
#endif
