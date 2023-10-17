#include "sub_commands.hpp"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <numeric>
#include <iofmtguard.hpp>

namespace zhuravlev
{
  int getXCoordinate(const Point& point)
  {
    return point.x;
  }
  int getYCoordinate(const Point& point)
  {
    return point.y;
  }
  int findMaxXInSinglePolygon(const Polygon& pl)
  {
    std::vector< int > x_values(pl.points.size());
    std::transform(pl.points.begin(), pl.points.end(), x_values.begin(), getXCoordinate);
    std::sort(x_values.begin(), x_values.end());
    return x_values.back();
  }
  int findMaxXInMultiplePolygons(const std::vector< Polygon >& pls)
  {
    std::vector< int > x_values(pls.size());
    std::transform(pls.begin(), pls.end(), x_values.begin(), findMaxXInSinglePolygon);
    std::sort(x_values.begin(), x_values.end());
    return x_values.back();
  }
  int findMinXInSinglePolygon(const Polygon& pl)
  {
    std::vector< int > x_values(pl.points.size());
    std::transform(pl.points.begin(), pl.points.end(), x_values.begin(), getXCoordinate);
    std::sort(x_values.begin(), x_values.end());
    return x_values.front();
  }
  int findMinXInMultiplePolygons(const std::vector< Polygon >& pls)
  {
    std::vector< int > x_values(pls.size());
    std::transform(pls.begin(), pls.end(), x_values.begin(), findMinXInSinglePolygon);
    std::sort(x_values.begin(), x_values.end());
    return x_values.front();
  }
  int findMaxYInSinglePolygon(const Polygon& pl)
  {
    std::vector< int > y_values(pl.points.size());
    std::transform(pl.points.begin(), pl.points.end(), y_values.begin(), getYCoordinate);
    std::sort(y_values.begin(), y_values.end());
    return y_values.back();
  }
  int findMaxYInMultiplePolygons(const std::vector< Polygon >& pls)
  {
    std::vector< int > y_values(pls.size());
    std::transform(pls.begin(), pls.end(), y_values.begin(), findMaxYInSinglePolygon);
    std::sort(y_values.begin(), y_values.end());
    return y_values.back();
  }
  int findMinYInSinglePolygon(const Polygon& pl)
  {
    std::vector< int > y_values(pl.points.size());
    std::transform(pl.points.begin(), pl.points.end(), y_values.begin(), getYCoordinate);
    std::sort(y_values.begin(), y_values.end());
    return y_values.front();
  }
  int findMinYInMultiplePolygons(const std::vector< Polygon >& pls)
  {
    std::vector< int > y_values(pls.size());
    std::transform(pls.begin(), pls.end(), y_values.begin(), findMinYInSinglePolygon);
    std::sort(y_values.begin(), y_values.end());
    return y_values.front();
  }
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
  void countOdd(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    iofmtguard iofmtguard(out);
    out << std::count_if(polygons.begin(), polygons.end(), isOdd) << '\n';
  }
  void countEven(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    iofmtguard iofmtguard(out);
    out << std::count_if(polygons.begin(), polygons.end(), isEven) << '\n';
  }
  void AreaEven(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    size_t size_of_even_vector = std::count_if(polygons.begin(), polygons.end(), isEven);
    std::vector< Polygon > even_polygons(size_of_even_vector);
    std::copy_if(polygons.begin(), polygons.end(), even_polygons.begin(), isEven);
    std::vector< double > areas_of_even(size_of_even_vector);
    std::transform(even_polygons.begin(), even_polygons.end(), areas_of_even.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(areas_of_even.begin(), areas_of_even.end(), 0.0) << '\n';
  }
  void AreaOdd(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    size_t size_of_odd_vector = std::count_if(polygons.begin(), polygons.end(), isOdd);
    std::vector< Polygon > odd_polygons(size_of_odd_vector);
    std::copy_if(polygons.begin(), polygons.end(), odd_polygons.begin(), isOdd);
    std::vector< double > areas_of_odd(size_of_odd_vector);
    std::transform(odd_polygons.begin(), odd_polygons.end(), areas_of_odd.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(areas_of_odd.begin(), areas_of_odd.end(), 0.0) << '\n';
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
    out << std::fixed << std::setprecision(1) << ((std::accumulate(areas.begin(), areas.end(), 0.0)) / (areas.size())) << "\n";
  }
  void AreaVertexes(const std::vector< Polygon >& polygons, std::ostream& out, const size_t condition)
  {
    if (condition < 3)
    {
      throw std::logic_error("There is no needed amount of vertexes...");
    }
    using namespace std::placeholders;
    size_t num_of_vertexes = condition;
    size_t size_of_needed_values = 0;
    size_of_needed_values = std::count_if(polygons.begin(), polygons.end(), std::bind(isRightNumberOfVertexes, _1, num_of_vertexes));
    std::vector< Polygon > needed_values(size_of_needed_values);
    std::copy_if(polygons.begin(), polygons.end(), needed_values.begin(), std::bind(isCountOfVertexes, _1, num_of_vertexes));
    std::vector< double > needed_area(size_of_needed_values);
    std::transform(needed_values.begin(), needed_values.end(), needed_area.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(needed_area.begin(), needed_area.end(), 0.0) << '\n';
  }
  void MaxArea(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("You need to add at least one polygon\n");
    }
    std::vector< double > all_areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), all_areas.begin(), getArea);
    std::sort(all_areas.begin(), all_areas.end());
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << all_areas.back() << '\n';
  }
  void MaxVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("You need to add at least one polygon\n");
    }
    std::vector< size_t > vertexes(polygons.size());
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(vertexes), getNumberOfVertexes);
    std::sort(vertexes.begin(), vertexes.end());
    iofmtguard iofmtguard(out);
    out << vertexes.back() << '\n';
  }
  void MinArea(const std::vector< Polygon >& polygons, std::ostream& out)
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
  void MinVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    std::vector< size_t > vertexes(polygons.size());
    std::transform(polygons.begin(), polygons.end(), vertexes.begin(), getNumberOfVertexes);
    std::sort(vertexes.begin(), vertexes.end());
    iofmtguard iofmtguard(out);
    out << vertexes.front() << '\n';
  }
  void countVertexes(const std::vector< Polygon >& polygons, std::ostream& out, const size_t condition)
  {
    if (condition < 3)
    {
      throw std::logic_error("Wrong condition");
    }
    using namespace std::placeholders;
    auto countNumOfRightPolygons = std::bind(isCountOfVertexes, _1, condition);
    iofmtguard iofmtguard(out);
    out << std::count_if(polygons.begin(), polygons.end(), countNumOfRightPolygons) << '\n';
  }
  bool isEqualSubCommand(const Polygon& lhs, const Polygon& rhs)
  {
    return std::equal(lhs.points.begin(), lhs.points.end(), rhs.points.begin(), rhs.points.end());
  }
  bool isEqualPolygon(const Polygon& polygon, const Polygon& first, const Polygon& second)
  {
    return isEqualSubCommand(first, second) && isEqualSubCommand(second, polygon);
  }
  void rmEcho(std::vector< zhuravlev::Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    Polygon polygon;
    in >> polygon;
    if (!in)
    {
      throw std::invalid_argument("not supported");
    }
    size_t result = 0;
    auto new_predicate = std::bind(isEqualPolygon, _1, _2, polygon);
    auto end = std::unique(polygons.begin(), polygons.end(), new_predicate);
    result = std::distance(end, polygons.end());
    polygons.erase(end, polygons.end());
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << result << "\n";
  }
  bool inReact(const Point& point, const int max_x, const int min_x, const int max_y, const int min_y)
  {
    return (point.x <= max_x && point.x >= min_x) && (point.y <= max_y && point.y >= min_y);
  }
  void inFrame(const std::vector< zhuravlev::Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    Polygon polygon;
    in >> polygon;
    if (polygon.points.size() != 4)
    {
      in.clear();
      throw std::invalid_argument("not supported");
    }
    if (!in)
    {
      in.clear();
      throw std::invalid_argument("not supported");
    }
    int max_x = findMaxXInMultiplePolygons(polygons);
    int max_y = findMaxYInMultiplePolygons(polygons);
    int min_x = findMinXInMultiplePolygons(polygons);
    int min_y = findMinYInMultiplePolygons(polygons);
    std::vector< bool > input_points(polygon.points.size());
    std::transform(polygon.points.begin(), polygon.points.end(), input_points.begin(), std::bind(inReact, _1, max_x, min_x, max_y, min_y));
    size_t sum = std::accumulate(input_points.begin(), input_points.end(), 0);
    if (sum == input_points.size())
    {
      out << "<TRUE>\n";
    }
    else
    {
      out << "<FALSE>\n";
    }
  }
  void printError(std::ostream& out)
  {
    out << "<INVALID COMMAND>" << '\n';
  }
}
