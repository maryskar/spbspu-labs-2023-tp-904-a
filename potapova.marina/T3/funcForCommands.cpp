#include "funcForCommands.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include "rectangle.h"

namespace potapova
{
  using namespace std::placeholders;

  double getTriangleArea(const Point& first_point, const Point& second_point)
  {
    return first_point.x * second_point.y - second_point.x * first_point.y;
  }

  double getPolygonArea(const Polygon& polygon)
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
      pair_areas.push_back(getTriangleArea(polygon.points.back(), polygon.points.front()));
    }
    return std::abs(std::accumulate(pair_areas.begin(), pair_areas.end(), 0.0)) / 2;
  }

  template< size_t ParityFlag >
  double addPolygonsAreaToSumT(const double sum, const Polygon& polygon)
  {
    if ((polygon.points.size() & 1) == ParityFlag)
    {
      return sum + getPolygonArea(polygon);
    }
    return sum;
  }

  template< size_t ParityFlag >
  double getSumPolygonsAreasT(const std::deque< Polygon >& polygons)
  {
    double area = std::accumulate(polygons.begin(), polygons.end(), 0.0, addPolygonsAreaToSumT< PartityFlag >);
    return area;
  }

  double addPolygonsAreaToSum(double& sum, const Polygon& polygon)
  {
    return sum + getPolygonArea(polygon);
  }

  double getSumPolygonsAreas(const std::deque< Polygon >& polygons)
  {
    double area = std::accumulate(polygons.begin(), polygons.end(), 0.0, addPolygonsAreaToSum);
    return area;
  }

  size_t countPolygons(const std::deque< Polygon >& polygons)
  {
    return polygons.size();
  }

  bool checkDesiredNumPoints(size_t num_points, const Polygon& polygon)
  {
    return polygon.points.size() == num_points;
  }

  double addAreaToSumIfNumPoints(double sum, const Polygon& polygon, size_t num_points)
  {
    if (checkDesiredNumPoints(num_points, polygon))
    {
      return sum + getPolygonArea(polygon);
    }
    return sum;
  }

  bool comparePolygonsAreas(const Polygon& first, const Polygon& second)
  {
    return getPolygonArea(first) < getPolygonArea(second);
  }

  bool comparePolygonsPoints(const Polygon& first, const Polygon& second)
  {
    return first.points.size() < second.points.size();
  }

  bool isOddPointNum(const Polygon& polygon)
  {
    return (polygon.points.size() & 1) == 1;
  }

  bool isEvenPointNum(const Polygon& polygon)
  {
    return (polygon.points.size() & 1) == 0;
  }

  bool operator==(const Polygon& first, const Polygon& second)
  {
    if (first.points.size() != second.points.size())
    {
      return false;
    }
    return std::equal(first.points.begin(), first.points.end(), second.points.begin());
  }

  bool comparePolygonsEqual(const Polygon& first, const Polygon& second, const Polygon& target_polygon)
  {
    return (first == second) && (first == target_polygon);
  }
}
