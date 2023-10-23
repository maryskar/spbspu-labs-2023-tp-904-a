#include "command.h"
#include <cmath>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <streamGuard.h>

namespace aristarkhov
{
  size_t getVerticesCount(const Polygon& polygon)
  {
    return polygon.points.size();
  }

  static double getTriangleArea(const aristarkhov::Point& lhs, const aristarkhov::Point& rhs)
  {
    return (lhs.x * rhs.y) - (lhs.y * rhs.x);
  }

  double getArea(const Polygon& polygon)
  {
    using namespace std::placeholders;

    std::vector< double > values(polygon.points.size());
    std::transform(polygon.points.begin(), --polygon.points.end(), ++polygon.points.begin(), std::back_inserter(values),
      getTriangleArea);
    values.push_back(getTriangleArea(polygon.points.back(), polygon.points.front()));
    double area = std::accumulate(values.begin(), values.end(), 0.0);
    area = std::abs(area / 2);

    return area;
  }

  bool isEven(const Polygon& polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool isOdd(const Polygon& polygon)
  {
    return !isEven(polygon);
  }

  void countOdd(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    StreamGuard iofmtguard(out);
    out << std::count_if(polygons.begin(), polygons.end(), isOdd) << '\n';
  }

  void countEven(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    StreamGuard iofmtguard(out);
    out << std::count_if(polygons.begin(), polygons.end(), isEven) << '\n';
  }

  double sumArea(double cur, const Polygon& polygon)
  {
    return cur + getArea(polygon);
  }

  void areaEven(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< Polygon > even_polygons;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(even_polygons), isEven);
    StreamGuard iofmtguard(out);
    out << std::fixed << std::setprecision(1)
      << std::accumulate(even_polygons.begin(), even_polygons.end(), 0.0, sumArea) << '\n';
  }

  void areaOdd(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< Polygon > odd_polygons;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(odd_polygons), isOdd);
    StreamGuard iofmtguard(out);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(odd_polygons.begin(), odd_polygons.end(), 0.0, sumArea) << "\n";
  }

  void areaMean(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("invalid arg\n");
    }

    size_t count = polygons.size();
    StreamGuard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0, sumArea) / count
      << "\n";
  }

  bool isCountOfVertexes(const Polygon& polygon, const size_t count)
  {
    return polygon.points.size() == count;
  }

  void areaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out)
  {
    using namespace std::placeholders;

    if (count < 3)
    {
      throw std::logic_error("invalid arg");
    }

    std::vector< Polygon > vertexes_polygons;
    auto pred = std::bind(isCountOfVertexes, _1, count);

    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(vertexes_polygons), pred);
    StreamGuard iofmtguard(out);

    out << std::fixed << std::setprecision(1)
      << std::accumulate(vertexes_polygons.begin(), vertexes_polygons.end(), 0.0, sumArea) << '\n';
  }
}
