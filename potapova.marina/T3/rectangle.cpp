#include "rectangle.h"
#include <numeric>
#include <algorithm>
#include <functional>
#include "dataStruct.h"
#include "commands.h"

namespace potapova
{
  using namespace std::placeholders;

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

  bool Rectangle::isInFrame(const Point& point)
  {
    return point.x >= min_x && point.x <= max_x && point.y >= min_y && point.y <= max_y;
  }

  bool Rectangle::isPolygonInFrame(const Polygon& polygon)
  {
    return std::all_of(polygon.points.begin(), polygon.points.end(), std::bind(&Rectangle::isInFrame, this, _1));
  }
}
