#include "commands.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <functional>

namespace shestakov
{
  bool isEven(const Polygon& polygon)
  {
    return !(polygon.points.size() % 2);
  }
  bool isOdd(const Polygon& polygon)
  {
    return (polygon.points.size() % 2);
  }
  size_t countVertexes(const Polygon& polygon)
  {
    return polygon.points.size();
  }
  bool equalVert(const Polygon& polygon, const size_t vert)
  {
    return polygon.points.size() == vert;
  }
  double getDeterminant(const Point& first, const Point& second)
  {
    int determinant = first.x * second.y - second.x * first.y;
    return determinant;
  }
  double getArea(const Polygon& polygon)
  {
    double area = 0.0;
    std::vector< double > side(polygon.points.size());
    std::transform(polygon.points.begin(), --polygon.points.end(), ++polygon.points.begin(), side.begin(), getDeterminant);
    area = std::accumulate(side.begin(), side.end(), 0.0);
    area += getDeterminant(polygon.points.front(), polygon.points.back());
    area = std::abs(area) / 2.0;
    return area;
  }
   void areaEven(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    size_t size_of_even = 0;
    double even_area = 0.0;
    size_of_even = std::count_if(polygons.begin(), polygons.end(), isEven);
    std::vector< double > ar_of_even_polygons(size_of_even);
    std::vector< Polygon > even_polygons(size_of_even);
    std::copy_if(polygons.begin(), polygons.end(), even_polygons.begin(), isEven);
    std::transform(even_polygons.begin(), even_polygons.end(), ar_of_even_polygons.begin(), getArea);
    even_area = std::accumulate(ar_of_even_polygons.begin(), ar_of_even_polygons.end(), 0.0);
    out << std::fixed << std::setprecision(1) << even_area << '\n';
  }
  void areaOdd(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    size_t size_of_odd = 0;
    double odd_area = 0.0;
    size_of_odd = std::count_if(polygons.begin(), polygons.end(), isOdd);
    std::vector< double > ar_of_odd_polygons(size_of_odd);
    std::vector< Polygon > odd_polygons(size_of_odd);
    std::copy_if(polygons.begin(), polygons.end(), odd_polygons.begin(), isOdd);
    std::transform(odd_polygons.begin(), odd_polygons.end(), ar_of_odd_polygons.begin(), getArea);
    odd_area = std::accumulate(ar_of_odd_polygons.begin(), ar_of_odd_polygons.end(), 0.0);
    out << std::fixed << std::setprecision(1) << odd_area << '\n';
  }
  void areaMean(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    double area_mean = 0.0;
    double area_sum = 0.0;
    std::vector< double > ar_of_polygons(polygons.size());
    std::transform(polygons.begin(), polygons.end(), ar_of_polygons.begin(), getArea);
    area_sum = std::accumulate(ar_of_polygons.begin(), ar_of_polygons.end(), 0.0);
    area_mean = area_sum / double(polygons.size());
    out << std::fixed << std::setprecision(1) << area_mean << '\n';
  }
  void maxArea(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< double > ar_of_polygons(polygons.size());
    std::transform(polygons.begin(), polygons.end(), ar_of_polygons.begin(), getArea);
    std::sort(ar_of_polygons.begin(), ar_of_polygons.end());
    out << std::fixed << std::setprecision(1) << ar_of_polygons[polygons.size() - 1] << '\n';
  }
  void minArea(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< double > ar_of_polygons(polygons.size());
    std::transform(polygons.begin(), polygons.end(), ar_of_polygons.begin(), getArea);
    std::sort(ar_of_polygons.begin(), ar_of_polygons.end());
    out << std::fixed << std::setprecision(1) << ar_of_polygons[0] << '\n';
  }
  void maxVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< size_t > count_vert(polygons.size());
    std::transform(polygons.begin(), polygons.end(), count_vert.begin(), countVertexes);
    std::sort(count_vert.begin(), count_vert.end());
    out << count_vert[polygons.size() - 1] << '\n';
  }
  void minVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< size_t > count_vert(polygons.size());
    std::transform(polygons.begin(), polygons.end(), count_vert.begin(), countVertexes);
    std::sort(count_vert.begin(), count_vert.end());
    out << count_vert[0] << '\n';
  }
  void countEven(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    size_t size_even = 0;
    size_even = std::count_if(polygons.begin(), polygons.end(), isEven);
    out << size_even << '\n';
  }
  void countOdd(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    size_t size_odd = 0;
    size_odd = std::count_if(polygons.begin(), polygons.end(), isOdd);
    out << size_odd << '\n';
  }
  void countVert(const std::vector< Polygon >& polygons, size_t num, std::ostream& out)
  {
    size_t num_of_vert = 0;
    std::vector< size_t > vert(polygons.size(), num);
    std::vector< bool > equal(polygons.size());
    std::transform(polygons.begin(), polygons.end(), vert.begin(), equal.begin(), equalVert);
    num_of_vert = std::accumulate(equal.begin(), equal.end(), 0);
    out << num_of_vert << '\n';
  }
  void areaVert(const std::vector< Polygon >& polygons, size_t num, std::ostream& out)
  {
    std::vector< Polygon > vert_polygons;
    double sum_areas = 0.0;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(vert_polygons), std::bind(equalVert, std::placeholders::_1, num));
    std::vector< double > areas(vert_polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), getArea);
    sum_areas = std::accumulate(areas.begin(), areas.end(), 0.0);
    out << std::fixed << std::setprecision(1) << sum_areas << '\n';
  }
  void printError(std::ostream& out)
  {
    out << "<INVALID COMMAND>";
  }
}
