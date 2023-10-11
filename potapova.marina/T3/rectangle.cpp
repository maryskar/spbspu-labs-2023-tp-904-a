#include "rectangle.h"
#include <numeric>
#include "dataStruct.h"
#include "commands.h"

namespace potapova
{
  Rectangle Rectangle::getRectWichCanInclude(const std::deque< Polygon >& polygons)
  {
    Rectangle rect;
    rect.expandBounds(polygons);
    return rect;
  }

  void Rectangle::expandBounds(const Point& point) noexcept
  {
    min_x = std::min(min_x, point.x);
    min_y = std::min(min_y, point.y);
    max_x = std::max(max_x, point.x);
    max_y = std::max(max_y, point.y);
  }

  void Rectangle::expandBounds(const Polygon& polygon) noexcept
  {
    std::copy(polygon.points.begin(), polygon.points.end(), RectExpandIterator(*this));
  }

  void Rectangle::expandBounds(const std::deque< Polygon >& polygons) noexcept
  {
    std::copy(polygons.begin(), polygons.end(), RectExpandIterator(*this));
  }

  bool Rectangle::isInFrame(const Rectangle& frame, const Point& point)
  {
    return point.x >= frame.min_x && point.x <= frame.max_x && point.y >= frame.min_y && point.y <= frame.max_y;
  }
}
