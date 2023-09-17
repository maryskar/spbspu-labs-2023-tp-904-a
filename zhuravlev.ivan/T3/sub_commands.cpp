#include "sub_commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <functional>
#include "iofmtguard.hpp"

namespace zhuravlev
{
  size_t getNumberOfVertexes(const Polygon& polygon)
  {
    return polygon.points.size();
  }
  bool isRightNumberOfVertexes(const Polygon& polygon, const size_t num_of_vertexes)
  {
    return polygon.points.size() == num_of_vertexes;
  }
  bool isCountOfVertexes(const Polygon& polygon, const size_t num_of_vertexes)
  {
    return polygon.points.size() == num_of_vertexes;
  }
  double getSide(const Point& lhs, const Point& rhs)
  {
    return ((lhs.x * rhs.y) - (lhs.y * rhs.x));
  }
  double getArea(const Polygon& polygon)
  {
    double area = 0.0;
    std::vector< int > sides(polygon.points.size());
    std::transform(polygon.points.begin(), --polygon.points.end(), ++polygon.points.begin(), std::back_inserter(sides), getSide);
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
  void countOdd(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out)
  {
    iofmtguard iofmtguard(out);
    out << std::count_if(polygons.begin(), polygons.end(), isOdd) << '\n';
  }
  void countEven(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out)
  {
    iofmtguard iofmtguard(out);
    out << std::count_if(polygons.begin(), polygons.end(), isEven) << '\n';
  }
  void AreaEven(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out)
  {
    size_t size_of_even_vector = std::count_if(polygons.begin(), polygons.end(), isEven);
    std::vector< Polygon > even_polygons(size_of_even_vector);
    std::copy_if(polygons.begin(), polygons.end(), even_polygons.begin(), isEven);
    std::vector< double > areas_of_even(size_of_even_vector);
    std::transform(even_polygons.begin(), even_polygons.end(), areas_of_even.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(areas_of_even.begin(), areas_of_even.end(), 0.0) << '\n';
  }
  void AreaOdd(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out)
  {
    size_t size_of_odd_vector = std::count_if(polygons.begin(), polygons.end(), isOdd);
    std::vector< Polygon > odd_polygons(size_of_odd_vector);
    std::copy_if(polygons.begin(), polygons.end(), odd_polygons.begin(), isOdd);
    std::vector< double > areas_of_odd(size_of_odd_vector);
    std::transform(odd_polygons.begin(), odd_polygons.end(), areas_of_odd.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(areas_of_odd.begin(), areas_of_odd.end(), 0.0) << '\n';
  }
  void AreaMean(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("You need to add at least one polygon\n");
    }
    std::vector< double > areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << ((std::accumulate(areas.begin(), areas.end(), 0.0)) / (areas.size())) << "\n";
  }
  void AreaVertexes(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    size_t num_of_vertexes;
    in >> num_of_vertexes;
    size_t size_of_needed_values = 0;
    size_of_needed_values = std::count_if(polygons.begin(), polygons.end(), std::bind(isRightNumberOfVertexes, _1, num_of_vertexes));
    std::vector< Polygon > needed_values(size_of_needed_values);
    std::copy_if(polygons.begin(), polygons.end(), needed_values.begin(), std::bind(isCountOfVertexes, _1, num_of_vertexes));
    std::vector< double > needed_area(size_of_needed_values);
    std::transform(needed_values.begin(), needed_values.end(), needed_area.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(needed_area.begin(), needed_area.end(), 0.0) << '\n';
  }
  void MaxArea(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("You need to add at least one polygon\n");
    }
    std::vector< double > all_areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), all_areas.begin(), getArea);
    std::sort(all_areas.begin(), all_areas.end());
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << all_areas.back() << '\n';
  }
  void MaxVertexes(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out)
  {
    std::vector< size_t > vertexes(polygons.size());
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(vertexes), getNumberOfVertexes);
    std::sort(vertexes.begin(), vertexes.end());
    iofmtguard iofmtguard(out);
    out << vertexes.back() << '\n';
  }
  void MinArea(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("You need to add at least one polygon\n");
    }
    std::vector< double > all_areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), all_areas.begin(), getArea);
    std::sort(all_areas.begin(), all_areas.end());
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << all_areas.front() << "\n";
  }
  void MinVertexes(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out)
  {
    std::vector< size_t > vertexes(polygons.size());
    std::transform(polygons.begin(), polygons.end(), vertexes.begin(), getNumberOfVertexes);
    std::sort(vertexes.begin(), vertexes.end());
    iofmtguard iofmtguard(out);
    out << vertexes.front() << '\n';
  }
  void countVertexes(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    size_t num_of_vertexes = 0;
    in >> num_of_vertexes;
    iofmtguard iofmtguard(out);
    out << std::count_if(polygons.begin(), polygons.end(), getNumberOfVertexes) << '\n';
  }
  void printError(std::ostream& out)
  {
    iofmtguard iofmtguard(out);
    out << "<INVALID COMMAND>" << '\n';
  }
}
