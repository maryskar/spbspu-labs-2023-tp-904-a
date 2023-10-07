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
  double addPolygonsAreaToSum(double& sum, const Polygon& polygon)
  {
    if ((polygon.points.size() & 1) == ParityFlag)
    {
      return sum + getPolygonArea(polygon);
    }
    return sum;
  }

  template< size_t ParityFlag >
  double getSumPolygonsAreas(const std::deque< Polygon >& polygons)
  {
    double area = std::accumulate(polygons.begin(), polygons.end(), 0.0, addPolygonsAreaToSum< PartityFlag >);
    return area;
  }

  size_t countPolygons(const std::deque< Polygon >& polygons)
  {
    return polygons.size();
  }

  template< size_t ParityFlag >
  double calculateAverageArea(const std::deque< Polygon >& polygons)
  {
    size_t num_polygons = countPolygons(polygons);
    if (num_polygons < 1)
    {
      throw std::runtime_error("Incorrect number of polygons");
    }
    double all_area = getSumPolygonsAreas< ParityFlag >(polygons);
    double average_area = all_area / num_polygons;
    return average_area;
  }

  void addPolygon(std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream&,
      std::ostream&)
  {
    Polygon input;
    if (in >> input)
    {
      polygons.push_back(input);
    } 
    else
    {
      throw std::logic_error("");
    }
  }

}
