#include "commands.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>
#include <stdexcept>

namespace potapova
{
  double calculateTriangleArea(const Point& first_point, const Point& second_point)
  {
    return first_point.x * second_point.y - second_point.x * first_point.y;
  }

  double calculatePolygonArea(const Polygon& polygon)
  {
    size_t num_points = polygon.points.size();
    std::vector< double > pair_areas(num_points);
    std::transform(polygon.points.begin(),
      polygon.points.end() - 1,
      polygon.points.begin() + 1,
      pair_areas.begin(),
      calculateTriangleArea);
    if (num_points % 2 != 0)
    {
      pair_areas.push_back(calculateTriangleArea(polygon.points.back(), polygon.points.front()));
    }
    double area = std::abs(std::accumulate(pair_areas.begin(), pair_areas.end(), 0.0)) / 2;
    return area;
  }

  size_t countPolygons(const std::deque< Polygon >& polygons)
  {
    return polygons.size();
  }

  double calculateSumPolygonsArea(double& sum, const Polygon& polygon)
  {
    return sum + calculatePolygonArea(polygon);
  }

  double calculateAverageArea(const std::deque< Polygon >& polygons)
  {
    size_t num_polygons = countPolygons(polygons);
    if (num_polygons < 1)
    {
      throw std::runtime_error("Incorrect number of polygons");
    }
    double average_area = std::accumulate(polygons.begin(), polygons.end(), 0.0, calculateSumPolygonsArea) / num_polygons;
    return average_area;
  }
}
