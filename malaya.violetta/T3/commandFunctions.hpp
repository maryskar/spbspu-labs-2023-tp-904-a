#ifndef T3_COMMANDFUNCTIONS_HPP
#define T3_COMMANDFUNCTIONS_HPP
#include "Polygon.hpp"

namespace malaya
{
  double areaEven(const Polygon & polygon);
  double areaOdd(const Polygon & polygon);
  double areaNum(const Polygon & polygon, size_t num);
  double maxArea(std::vector< malaya::Polygon > data);
}

#endif
