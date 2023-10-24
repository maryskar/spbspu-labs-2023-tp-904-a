#include "dataStructs.h"
#include <algorithm>

bool potapova::operator==(const Point& first, const Point& second) noexcept
{
  return first.x == second.x && first.y == second.y;
}

bool potapova::operator==(const Polygon& first, const Polygon& second) noexcept
{
  if (first.points.size() != second.points.size())
  {
    return false;
  }
  return std::equal(first.points.begin(), first.points.end(), second.points.begin());
}
