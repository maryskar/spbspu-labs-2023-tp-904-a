#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <limits>
#include <deque>

namespace potapova
{
  class Rectangle
  {
    private:
      int max_x;
      int min_x;
      int max_y;
      int min_y;

      static Rectangle accumulatePolygons(Rectangle accumulator, const Polygon& polygon);
    public:
      Rectangle():
        max_x(std::numeric_limits< int >::max()),
        min_x(std::numeric_limits< int >::lowest()),
        max_y(std::numeric_limits< int >::max()),
        min_y(std::numeric_limits< int >::lowest())
      {

      }

      static Rectangle getRectWichCanInclude(const std::deque< Polygon >& polygons);
      void expandBoundsToPoint(Rectangle& rectangle, const Point& point);
      bool isPointInFrame(const Rectangle& frame, const Point& point);
  };
}

#endif
