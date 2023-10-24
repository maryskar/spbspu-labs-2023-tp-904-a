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
    std::transform(polygon.points.begin(), --polygon.points.end(), ++polygon.points.begin(), std::back_inserter(values), getTriangleArea);
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
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(even_polygons.begin(), even_polygons.end(), 0.0, sumArea) << '\n';
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

    out << std::fixed << std::setprecision(1);
    out << std::accumulate(polygons.begin(), polygons.end(), 0.0, sumArea) / count << "\n";
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

    out << std::fixed << std::setprecision(1);
    out << std::accumulate(vertexes_polygons.begin(), vertexes_polygons.end(), 0.0, sumArea) << '\n';
  }

  void maxArea(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("invalid arg");
    }

    std::vector< double > all_areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), all_areas.begin(), getArea);
    std::sort(all_areas.begin(), all_areas.end());

    StreamGuard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << all_areas.back() << "\n";
  }

  void minArea(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("invalid arg");
    }

    std::vector< double > all_areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), all_areas.begin(), getArea);
    std::sort(all_areas.begin(), all_areas.end());

    StreamGuard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << all_areas.front() << "\n";
  }

  void maxVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("invalid arg");
    }

    std::vector< size_t > vertexes(polygons.size());
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(vertexes), getVerticesCount);
    std::sort(vertexes.begin(), vertexes.end());

    StreamGuard iofmtguard(out);
    out << vertexes.back() << "\n";
  }

  void minVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::logic_error("invalid arg");
    }

    std::vector< size_t > vertexes(polygons.size());
    std::transform(polygons.begin(), polygons.end(), vertexes.begin(), getVerticesCount);
    std::sort(vertexes.begin(), vertexes.end());

    StreamGuard iofmtguard(out);
    out << vertexes.front() << "\n";
  }

  void countVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out)
  {
    if (count < 3)
    {
      throw std::logic_error("invalid arg");
    }

    using namespace std::placeholders;
    auto pred = std::bind(isCountOfVertexes, _1, count);

    StreamGuard iofmtguard(out);
    out << count_if(polygons.begin(), polygons.end(), pred) << "\n";
  }

  bool isEqualPolygon(const Polygon& lhs, const Polygon& rhs, const aristarkhov::Polygon& polygon)
  {
    return (rhs == lhs) && (rhs == polygon);
  }

  void rmEcho(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out)
  {
    using namespace std::placeholders;

    size_t result = 0;
    auto new_pred = std::bind(isEqualPolygon, _1, _2, polygon);
    auto end = std::unique(polygons.begin(), polygons.end(), new_pred);

    result = std::distance(end, polygons.end());
    polygons.erase(end, polygons.end());

    StreamGuard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << result << "\n";
  }

  bool lessX(aristarkhov::Point lhs, aristarkhov::Point rhs)
  {
    return lhs.x < rhs.x;
  }

  bool lessY(aristarkhov::Point lhs, aristarkhov::Point rhs)
  {
    return lhs.y < rhs.y;
  }

  aristarkhov::Frame getFrame(const Polygon& polygon)
  {
    auto begin = polygon.points.begin();
    auto end = polygon.points.end();

    int minX = std::min_element(begin, end, lessX)->x;
    int maxX = std::max_element(begin, end, lessX)->x;
    int minY = std::min_element(begin, end, lessY)->y;
    int maxY = std::max_element(begin, end, lessY)->y;

    return { {minX, minY}, {maxX, maxY} };
  }

  aristarkhov::Frame correctFrame(aristarkhov::Frame result, aristarkhov::Frame value)
  {
    int minX = lessX(result.first, value.first) ? result.first.x : value.first.x;
    int maxX = lessX(result.second, value.second) ? value.second.x : result.second.x;
    int minY = lessY(result.first, value.first) ? result.first.y : value.first.y;
    int maxY = lessY(result.second, value.second) ? value.second.y : result.second.y;

    return { {minX, minY}, {maxX, maxY} };
  }

  aristarkhov::Frame getPolygonsFrame(std::vector< Polygon > data)
  {
    auto begin = data.begin();
    auto end = data.end();

    std::vector< aristarkhov::Frame > frames;
    std::transform(begin, end, std::back_inserter(frames), aristarkhov::getFrame);

    aristarkhov::Frame frame = *frames.begin();
    return std::accumulate(frames.begin() + 1, frames.end(), frame, correctFrame);
  }

  bool isFrameInFrame(const Frame& lhs, const Frame& rhs)
  {
    bool case1 = !lessX(lhs.first, rhs.first);
    bool case2 = !lessY(lhs.first, rhs.first);
    bool case3 = !lessX(rhs.second, lhs.second);
    bool case4 = !lessY(rhs.second, lhs.second);

    return case1 && case2 && case3 && case4;
  }

  void printBool(std::ostream& out, bool value)
  {
    if (value)
    {
      out << "<TRUE>";
    }
    else
    {
      out << "<FALSE>";
    }
  }

  void printInFrame(std::vector< Polygon >& polygons, const Polygon& figure, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("empty polygons");
    }

    printBool(out, isFrameInFrame(getFrame(figure), getPolygonsFrame(polygons)));
  }
}
