#include "is-nearly-equal.hpp"
#include <cassert>
#include <cmath>
#include <algorithm>

bool chemodurov::isNearlyEqual(double lhs, double rhs, double epsilon, double abs_th)
{
  assert(std::numeric_limits< double >::epsilon() <= epsilon);
  assert(epsilon < 1.0);
  if (lhs == rhs)
  {
    return true;
  }
  double diff = std::abs(lhs - rhs);
  double norm = std::min(std::abs(lhs) + std::abs(rhs), std::numeric_limits< double >::max());
  return diff < std::max(abs_th, epsilon * norm);
}
