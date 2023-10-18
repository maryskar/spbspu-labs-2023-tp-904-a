#ifndef HELP_STRUCTURES_H
#define HELP_STRUCTURES_H
#include "polygon.h"
#include "help_commands.h"
namespace skarlygina
{
  struct PolygonsArea
  {
    PolygonsArea(Point point):
      prev(point)
    {}
    double operator()(double area, const Point& current)
    {
      area += static_cast< double >(prev.x) * current.y;
      area -= static_cast< double >(prev.y) * current.x;
      prev = current;
      return area;
    }
  private:
    Point prev;
  };

  template< class Condition >
  struct AreaCondition
  {
    AreaCondition(Condition cond):
      condition(cond)
    {}

    double operator()(double area, const Polygon& poly)
    {
      if (condition(poly))
      {
        return area + findAreaPoly(poly);
      }
      return area;
    }
  private:
    Condition condition;
  };
}
#endif
