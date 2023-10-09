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

  void getSumAreasPolygonsOdd(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    double sum = getSumPolygonsAreasT<ODD>(polygons);
    out << sum << '\n';
  }

  void getSumAreasPolygonsEven(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    double sum = getSumPolygonsAreasT<EVEN>(polygons);
    out << sum << '\n';
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
      std::ostream& out,
      std::ostream&)
  {
    size_t num_polygons = countPolygons(polygons);
    if (num_polygons < 1)
    {
      throw std::runtime_error("Incorrect number of polygons");
    }
    double all_area = getSumPolygonsAreas(polygons);
    double average_area = all_area / num_polygons;
    out << average_area << '\n';
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
      std::ostream& out,
      std::ostream&)
  {
    size_t num_points = 0;
    in >> num_points;
    double sum_areas = std::accumulate(polygons.begin(), polygons.end(), 0.0, addAreaToSumIfNumPoints);
    out << sum_areas << '\n';
  }

  bool comparePolygonsAreas(const Polygon& first, const Polygon& second)
  {
    return getPolygonArea(first) < getPolygonArea(second);
  }

  void getMaxArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Invalid number of polygons");
    }
    auto max_polygon_iter = std::max_element(polygons.begin(), polygons.end(), comparePolygonsAreas);
    double max_area = getPolygonArea(*max_polygon_iter);
    out << max_area << '\n';
  }

  bool comparePolygonsPoints(const Polygon& first, const Polygon& second)
  {
    return first.points.size() < second.points.size();
  }

  void getMaxPoints(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Invalid number of polygons");
    }
    auto max_polygon_iter = std::max_element(polygons.begin(), polygons.end(), comparePolygonsPoints);
    double max_points = max_polygon_iter->points.size();
    out << max_points << '\n';
  }

  void getMinArea(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Invalid number of polygons");
    }
    auto min_polygon_iter = std::min_element(polygons.begin(), polygons.end(), comparePolygonsAreas);
    double min_area = getPolygonArea(*min_polygon_iter);
    out << min_area << '\n';
  }

  void getMaxPoints(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Invalid number of polygons");
    }
    auto min_polygon_iter = std::min_element(polygons.begin(), polygons.end(), comparePolygonsPoints);
    double min_points = min_polygon_iter->points.size();
    out << min_points << '\n';
  }

  bool isOddPointNum(const Polygon& polygon)
  {
    return (polygon.points.size() & 1) == 1;
  }

  void countPolygonsWithOddPointsNum(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    size_t num_polygons = std::count_if(polygons.begin(), polygons.end(), isOddPointNum);
    out << num_polygons << '\n';
  }

  bool isEvenPointNum(const Polygon& polygon)
  {
    return (polygon.points.size() & 1) == 0;
  }

  void countPolygonsWithEvenPointsNum(const std::deque< Polygon >& polygons,
      std::istream&,
      std::ostream& out,
      std::ostream&)
  {
    size_t num_polygons = std::count_if(polygons.begin(), polygons.end(), isEvenPointNum);
    out << num_polygons << '\n';
  }

  void countPolygonsWithPointsNum(const std::deque< Polygon >& polygons,
      std::istream& in,
      std::ostream& out,
      std::ostream&)
  {
    size_t num_points = 0;
    in >> num_points;
    size_t num_polygons = std::count_if(polygons.begin(), polygons.end(), checkDesiredNumPoints);
    out << num_polygons << '\n';
  }
}
