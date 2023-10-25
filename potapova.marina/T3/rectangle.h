#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <deque>
#include "dataStructs.h"

namespace potapova
{
  class Rectangle
  {
    public:
      Rectangle(const Polygon& startBounds) noexcept;
      Rectangle* expandBoundsToPoint(const Point& point) noexcept;
      Rectangle* expandBoundsToPolygon(const Polygon& polygon) noexcept;
      Rectangle* expandBoundsToPolygons(const std::deque< Polygon >& polygons) noexcept;
      bool isPointInFrame(const Point& point) noexcept;
      bool isPolygonInFrame(const Polygon& polygon) noexcept;
    private:
      int max_x;
      int min_x;
      int max_y;
      int min_y;
  };
}

#endif
