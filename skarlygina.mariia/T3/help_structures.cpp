#include "help_structures.h"
namespace skarlygina
{
  PolygonsArea::PolygonsArea(Point point):
    prev(point)
  {}
  double PolygonsArea::operator()(double area, const Point& current)
  {
    area += static_cast<double>(prev.x) * current.y;
    area -= static_cast<double>(prev.y) * current.x;
    prev = current;
    return area;
  }
}
