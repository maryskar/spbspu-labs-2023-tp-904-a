#include "sub_commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include "iofmtguard.hpp"

namespace zhuravlev
{
  bool isCountOfVertexes(const Polygon& polygon, const size_t num_of_vertexes)
  {
    return polygon.points.size() == num_of_vertexes;
  }
  double getSide(const Point& lhs, const Point& rhs)
  {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
  double getArea(const Polygon& polygon)
  {
    double area = 0.0;
    std::vector< int > sides(polygon.points.size());
    std::transform(polygon.points.begin(), polygon.points.end() - 1, polygon.points.begin()++, std::back_inserter(sides), getSide);
    area = std::accumulate(sides.begin(), sides.end(), 0.0);
    area += getSide(polygon.points.back(), polygon.points.front());
    return std::abs(area * 0.5);
  }
  bool isEven(const Polygon& polygons)
  {
    return (polygons.points.size()) % 2 == 0;
  }
  bool isOdd(const Polygon& polygons)
  {
    return !isEven(polygons);
  }
  void countOdd(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    iofmtguard iofmtguard(out);
    out << std::count_if(polygons.begin(), polygons.end(), isOdd);
  }
  void countEven(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    iofmtguard iofmtguard(out);
    out << std::count_if(polygons.begin(), polygons.end(), isEven);
  }
  void AreaEven(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< Polygon > even_polygons(polygons.size());
    std::copy_if(polygons.begin(), polygons.end(), even_polygons.begin(), isEven);
    std::vector< double > areas_of_even(even_polygons.size());
    std::transform(even_polygons.begin(), even_polygons.end(), areas_of_even.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(areas_of_even.begin(), areas_of_even.end(), 0.0); 
  }
  void AreaOdd(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< Polygon > even_polygons(polygons.size());
    std::copy_if(polygons.begin(), polygons.end(), even_polygons.begin(), isOdd);
    std::vector< double > areas_of_odd(even_polygons.size());
    std::transform(even_polygons.begin(), even_polygons.end(), areas_of_odd.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(areas_of_odd.begin(), areas_of_odd.end(), 0.0); 
  }
  void AreaMean(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("You need to add at least one polygon\n");
    }
    std::vector< double > areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << ((std::accumulate(areas.begin(), areas.end(), 0.0)) / (areas.size()));
  }
  void AreaVertexes(const std::vector< Polygon >& polygons, size_t num_of_vertexes, std::ostream& out)
  {
    using namespace std::placeholders;
    std::vector< Polygon > needed_values(polygons.size());
    std::copy_if(polygons.begin(), polygons.end(), needed_values.begin(), std::bind(isCountOfVertexes, _1, num_of_vertexes));
    std::vector< double > needed_area(needed_area.size());
    std::transform(needed_area.begin(), needed_area.end(), needed_values.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(needed_area.begin(), needed_area.end(), 0.0);
  }
  void MaxArea(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("You need to add at least one polygon\n");
    }
    std::vector< double > all_areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(all_areas), getArea);
    std::sort(all_areas.begin(), all_areas.end());
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << all_areas.back();
  }
  void MaxVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< size_t > vertexes(polygons.size());
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(vertexes), polygons.size());
    std::sort(vertexes.begin(), vertexes.end());
    iofmtguard iofmtguard(out);
    out << vertexes.back();
  }
  void MinArea(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("You need to add at least one polygon\n");
    }
    std::vector< double > all_areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(all_areas), getArea);
    std::sort(all_areas.begin(), all_areas.end());
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << all_areas.front();
  }
  void MinVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< size_t > vertexes(polygons.size());
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(vertexes), polygons.size());
    std::sort(vertexes.begin(), vertexes.end());
    iofmtguard iofmtguard(out);
    out << vertexes.front();
  }
  void countVertexes(const std::vector< Polygon >& polygons, const size_t num_of_vertexes, std::ostream& out)
  {
    iofmtguard iofmtguard(out);
    out << std::count_if(polygons.begin(), polygons.end(), num_of_vertexes);
  }
}
