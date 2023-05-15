#ifndef T3_GETAREA_HPP
#define T3_GETAREA_HPP
#include "Polygon.hpp"

namespace malaya
{
  double getArea(const malaya::Polygon & polygon);
  struct areaCounter
  {
    double operator()(const Point & left, const Point & right);
  };
}

#endif
