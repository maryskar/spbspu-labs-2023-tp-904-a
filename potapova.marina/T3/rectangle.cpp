#include "rectangle.h"
#include <limits>
#include <numeric>
#include <algorithm>
#include <functional>
#include "commands.h"

using namespace std::placeholders;

potapova::Rectangle::Rectangle(const Polygon& startBounds) noexcept:
  max_x(std::numeric_limits< int >::lowest()),
  min_x(std::numeric_limits< int >::max()),
  max_y(std::numeric_limits< int >::lowest()),
  min_y(std::numeric_limits< int >::max())
{
  expandBoundsToPolygon(startBounds);
}

potapova::Rectangle* potapova::Rectangle::expandBoundsToPoint(const Point& point) noexcept
{
  min_x = std::min(min_x, point.x);
  min_y = std::min(min_y, point.y);
  max_x = std::max(max_x, point.x);
  max_y = std::max(max_y, point.y);
  return this;
}

potapova::Rectangle* potapova::Rectangle::expandBoundsToPolygon(const Polygon& polygon) noexcept
{
  std::accumulate(polygon.points.begin(), polygon.points.end(), this, std::bind(&Rectangle::expandBoundsToPoint, _1, _2));
  return this;
}

potapova::Rectangle* potapova::Rectangle::expandBoundsToPolygons(const std::deque< Polygon >& polygons) noexcept
{
  std::accumulate(polygons.begin(), polygons.end(), this, std::bind(&Rectangle::expandBoundsToPolygon, _1, _2));
  return this;
}

bool potapova::Rectangle::isPointInFrame(const Point& point) noexcept
{
  return point.x >= min_x && point.x <= max_x && point.y >= min_y && point.y <= max_y;
}

bool potapova::Rectangle::isPolygonInFrame(const Polygon& polygon) noexcept
{
  return std::all_of(polygon.points.begin(), polygon.points.end(), std::bind(&Rectangle::isPointInFrame, this, _1));
}
