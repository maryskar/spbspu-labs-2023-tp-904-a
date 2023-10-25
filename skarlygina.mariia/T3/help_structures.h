#ifndef HELP_STRUCTURES_H
#define HELP_STRUCTURES_H
#include "polygon.h"
namespace skarlygina
{
  struct PolygonsArea
  {
    PolygonsArea(Point point);
    double operator()(double area, const Point& current);
  private:
    Point prev;
  };
}
#endif
