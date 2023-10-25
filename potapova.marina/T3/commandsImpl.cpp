#include "commandsImpl.h"
#include <algorithm>
#include <stdexcept>
#include <iterator>

namespace
{
  double getTriangleArea(const potapova::Point& first_point, const potapova::Point& second_point)
  {
    return first_point.x * second_point.y - second_point.x * first_point.y;
  }
}

double potapova::getArea(const Polygon& polygon)
{
  size_t countPoints = polygon.points.size();
  std::vector< double > values(countPoints - 1);
  std::vector< Point >::const_iterator begin_ptr = polygon.points.begin();
  std::vector< Point >::const_iterator second_elem_ptr = begin_ptr + 1;
  std::vector< Point >::const_iterator end_ptr = polygon.points.end() - 1;
  std::transform(begin_ptr, end_ptr, second_elem_ptr, std::back_inserter(values), getTriangleArea);
  double area = std::accumulate(values.begin(), values.end(), 0.0);
  area += getTriangleArea(polygon.points.back(), polygon.points.front());
  area = std::abs(area) / 2;
  return area;
}

double potapova::addAreaToSum(const double sum, const Polygon& polygon)
{
  return sum + getArea(polygon);
}

double potapova::getSumOfAreas(const std::deque< Polygon >& polygons)
{
  double area = std::accumulate(polygons.begin(), polygons.end(), 0.0, addAreaToSum);
  return area;
}

bool potapova::checkDesiredNumPoints(size_t num_points, const potapova::Polygon& polygon) noexcept
{
  return polygon.points.size() == num_points;
}

double potapova::addAreaToSumIfNumPoints(double sum, const Polygon& polygon, size_t num_points)
{
  if (checkDesiredNumPoints(num_points, polygon))
  {
    return sum + getArea(polygon);
  }
  return sum;
}

bool potapova::comparePolygonsAreas(const Polygon& first, const Polygon& second)
{
  return getArea(first) < getArea(second);
}

bool potapova::comparePolygonsPoints(const Polygon& first, const Polygon& second)
{
  return first.points.size() < second.points.size();
}

bool potapova::isEqual(const Polygon& first, const Polygon& second, const Polygon& third) noexcept
{
  return (first == second) && (first == third);
}
