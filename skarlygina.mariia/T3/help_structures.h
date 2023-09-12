#ifndef HELP_STRUCTURES_H
#define HELP_STRUCTURES_H
#include "polygon.h"
namespace skarlygina
{
  struct PolygonsArea
  {
    PolygonsArea(skarlygina::Point point) :
      prev(point)
    {}
    double operator()(double area, const skarlygina::Point& current)
    {
      area += static_cast<double>(prev.x) * current.y;
      area -= static_cast<double>(prev.y) * current.x;
      prev = current;
      return area;
    }
  private:
    skarlygina::Point prev;
  };

  template< class Condition >
  struct AreaCondition
  {
    AreaCondition(Condition cond) :
      condition(cond)
    {}

    double operator()(double area, const skarlygina::Polygon& poly)
    {
      if (condition(poly)) {
        return area + skarlygina::getAreaPolygon(poly);
      }
      return area;
    }
  private:
    Condition condition;
  };
}

#endif
