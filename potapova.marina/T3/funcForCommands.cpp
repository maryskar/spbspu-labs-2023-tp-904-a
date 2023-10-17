#include "funcForCommands.h"
#include <algorithm>

namespace potapova
{
  double getTriangleArea(const Point& first_point, const Point& second_point)
  {
    return first_point.x * second_point.y - second_point.x * first_point.y;
  }

  double getArea(const Polygon& polygon)
  {
    size_t num_points = polygon.points.size();
    if (num_points < 3)
    {
      throw std::logic_error("Invalid polygon");
    }
    std::vector< double > pair_areas(num_points);
    std::transform(polygon.points.begin(),
      polygon.points.end() - 1,
      polygon.points.begin() + 1,
      pair_areas.begin(),
      getTriangleArea);
    if ((num_points & 1) == 1)
    {
      pair_areas.emplace_back(getTriangleArea(polygon.points.back(), polygon.points.front()));
    }
    return std::abs(std::accumulate(pair_areas.begin(), pair_areas.end(), 0.0)) / 2;
  }

  double addAreaToSumT(const double sum, const Polygon& polygon)
  {
    return sum + getArea(polygon);
  }

  double getSumOfAreas(const std::deque< Polygon >& polygons)
  {
    double area = std::accumulate(polygons.begin(), polygons.end(), 0.0, addAreaToSum);
    return area;
  }

  bool checkDesiredNumPoints(size_t num_points, const potapova::Polygon& polygon) noexcept
  {
    return polygon.points.size() == num_points;
  }

  double addAreaToSumIfNumPoints(double sum, const Polygon& polygon, size_t num_points)
  {
    if (checkDesiredNumPoints(num_points, polygon))
    {
      return sum + getArea(polygon);
    }
    return sum;
  }

  bool comparePolygonsAreas(const Polygon& first, const Polygon& second)
  {
    return getArea(first) < getArea(second);
  }

  bool comparePolygonsPoints(const Polygon& first, const Polygon& second)
  {
    return first.points.size() < second.points.size();
  }

  bool isEvenPointNum(const Polygon& polygon) noexcept
  {
    return (polygon.points.size() & 1) == EVEN;
  }

  bool isOddPointNum(const Polygon& polygon) noexcept
  {
    return (polygon.points.size() & 1) == ODD;
  }

  bool isEqual(const Polygon& first, const Polygon& second, const Polygon& third) noexcept
  {
    return (first == second) && (first == third);
  }
}
