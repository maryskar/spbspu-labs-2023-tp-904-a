#include "commands.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>
#include <stdexcept>

namespace potapova
{
  constexpr size_t ODD = 1;
  constexpr size_t EVEN = 0;

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
    double area = std::abs(std::accumulate(pair_areas.begin(), pair_areas.end(), 0.0)) / 2;
    return area;
  }

  template< size_t ParityFlag >
  double addPolygonsAreaToSumT(double& sum, const Polygon& polygon)
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

  void getSumAreasPolygonsOdd(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream&,
      std::ostream&)
  {
    double sum = getSumPolygonsAreasT<ODD>(polygons);
  }

  void getSumAreasPolygonsEven(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream&,
      std::ostream&)
  {
    double sum = getSumPolygonsAreasT<EVEN>(polygons);
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

  void getAverageArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream&,
      std::ostream&)
  {
    size_t num_polygons = countPolygons(polygons);
    if (num_polygons < 1)
    {
      throw std::runtime_error("Incorrect number of polygons");
    }
    double all_area = getSumPolygonsAreas(polygons);
    double average_area = all_area / num_polygons;
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

  void getSumOfAreasWithPointCounts(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream&,
      std::ostream&)
  {
    size_t num_points = 0;
    in >> num_points;
    double sum_areas = std::accumulate(polygons.begin(), polygons.end(), 0.0, addAreaToSumIfNumPoints);
  }

  bool comparePolygonsAreas(const Polygon& first, const Polygon& second)
  {
    return getPolygonArea(first) < getPolygonArea(second);
  }

  void getMaxArea(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream&,
      std::ostream&)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Invalid number of polygons");
    }
    auto max_polygon_iter = std::max_element(polygons.begin(), polygons.end(), comparePolygonsAreas);
    double max_area = getPolygonArea(*max_polygon_iter);
  }
}
