#include "rectangle.h"
#include <numeric>
#include "dataStruct.h"
#include "commands.h"

namespace potapova
{
  Rectangle Rectangle::accumulatePolygons(Rectangle accumulator, const Polygon& polygon)
  {
    return std::accumulate(polygon.points.begin(), polygon.points.end(), accumulator, expandBoundsToPoint);
  }

  Rectangle Rectangle::getRectWichCanInclude(const std::deque< Polygon >& polygons)
  {
    return std::accumulate(polygons.begin(), polygons.end(), Rectangle(), accumulatePolygons);
  }

  void Rectangle::expandBoundsToPoint(Rectangle& rectangle, const Point& point)
  {
    rectangle.min_x = std::min(rectangle.min_x, point.x);
    rectangle.min_y = std::min(rectangle.min_y, point.y);
    rectangle.max_x = std::max(rectangle.max_x, point.x);
    rectangle.max_y = std::max(rectangle.max_y, point.y);
  }

  bool Rectangle::isPointInFrame(const Rectangle& frame, const Point& point)
  {
    return point.x >= frame.min_x && point.x <= frame.max_x && point.y >= frame.min_y && point.y <= frame.max_y;
  }
}
