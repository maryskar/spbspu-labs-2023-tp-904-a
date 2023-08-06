#ifndef T3_IS_NEARLY_EQUAL_HPP
#define T3_IS_NEARLY_EQUAL_HPP
#include <limits>
#include <cfloat>

namespace chemodurov
{
  bool isNearlyEqual(double lhs, double rhs, double epsilon = 128 * DBL_EPSILON, double abs_th = DBL_MIN);
}

#endif
