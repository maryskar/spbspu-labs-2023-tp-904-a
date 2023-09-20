#include "extra_commands.h"
#include <math.h>
namespace mishanina
{
  bool isEven(const Polygon &polygon)
  {
    return polygon.points.size() % 2 == 0;
  }
  bool isOdd(const Polygon &polygon)
  {
    return !isEven(polygon);
  }
  bool isCountOfVertexes(const Polygon &polygon, std::size_t num)
  {
    return (polygon.points.size() == num);
  }
  std::size_t getNumOfVertexes(const Polygon &polygon)
  {
    return polygon.points.size();
  }
  double getSide(const Point &p1, const Point &p2)
  {
    return p1.x * p2.y - p1.y * p2.x;
  }
  double getArea(const Polygon &polygon)
  {
    double area;
    std::vector<int> arr(polygon.points.size());
    std::transform(polygon.points.begin(), --polygon.points.end(), ++polygon.points.begin(), std::back_inserter(arr),
                   getSide);
    area = std::accumulate(arr.begin(), arr.end(), 0.0);
    area +=
      (--polygon.points.end())->x * polygon.points.begin()->y - polygon.points.begin()->x * (--polygon.points.end())->y;
    return std::abs(area) / 2.0;
  }
  double getTotalArea(const std::vector<Polygon> &pol)
  {
    std::vector<double> areas(pol.size());
    std::transform(pol.begin(), pol.end(), areas.begin(), getArea);
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
    return sum;
  }
  std::size_t getMaxMinVert(const std::vector<Polygon> &polygons, bool isMax)
  {
    std::vector<std::size_t> points(polygons.size());
    std::transform(polygons.begin(), polygons.end(), points.begin(), getNumOfVertexes);
    auto res = isMax ? std::max_element(points.begin(), points.end()) : std::min_element(points.begin(), points.end());
    return *res;
  }
  double getMaxMinArea(const std::vector<Polygon> &polygons, bool isMax)
  {
    std::vector<double> areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), getArea);
    auto res = isMax ? std::max_element(areas.begin(), areas.end()) : std::min_element(areas.begin(), areas.end());
    return *res;
  }
  std::vector<Polygon> getPolygonsWithNumOfVertexes(const std::vector<Polygon> &polygons, std::size_t num)
  {
    using namespace std::placeholders;
    auto countVertexes = std::bind(isCountOfVertexes, _1, num);
    std::vector<Polygon> result;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(result), countVertexes);
    return result;
  }
  double getSideF(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
  }
  bool isParallelorgam(double side1, double side2, double side3, double side4) {
    return ((side1 == side3) && (side2 == side4));
  }
  bool isRectangle(const Polygon& polygon) {
    if (!isCountOfVertexes(polygon, 4ull))
    {
      return false;
    }

    double s1 = getSideF(polygon.points[0], polygon.points[1]);
    double s2 = getSideF(polygon.points[1], polygon.points[2]);
    double s3 = getSideF(polygon.points[2], polygon.points[3]);
    double s4 = getSideF(polygon.points[3], polygon.points[0]);

    double d1 = getSideF(polygon.points[0], polygon.points[2]);
    double d2 = getSideF(polygon.points[1], polygon.points[3]);

    return (isParallelorgam(s1, s2, s3, s4) && (d1 == d2));
  }
}