#include "rectangle.h"
#include <numeric>
#include <algorithm>
#include <functional>
#include "dataStruct.h"
#include "commands.h"

namespace potapova
{
  using namespace std::placeholders;

  Rectangle::Rectangle() noexcept:
    max_x(std::numeric_limits< int >::max()),
    min_x(std::numeric_limits< int >::lowest()),
    max_y(std::numeric_limits< int >::max()),
    min_y(std::numeric_limits< int >::lowest())
  {

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

  bool Rectangle::isPointInFrame(const Point& point) noexcept
  {
    return point.x >= min_x && point.x <= max_x && point.y >= min_y && point.y <= max_y;
  }

  bool Rectangle::isPolygonInFrame(const Polygon& polygon) noexcept
  {
    return std::all_of(polygon.points.begin(), polygon.points.end(), std::bind(&Rectangle::isPointInFrame, this, _1));
  }

  Rectangle::RectExpandIterator::RectExpandIterator(Rectangle& rect) noexcept:
    rect_ptr_(&rect)
  {

  }

  Rectangle::RectExpandIterator& Rectangle::RectExpandIterator::operator++() noexcept
  {
    return *this;
  }

  Rectangle::RectExpandIterator& Rectangle::RectExpandIterator::operator*() noexcept
  {
    return *this;
  }
}
