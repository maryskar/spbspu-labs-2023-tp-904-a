#include "extra_commands.h"

namespace mishanina{
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
  double getSide(const Point& p1, const Point& p2){
    return p1.x * p2.y - p1.y * p2.x;
  }
  double getArea(const Polygon& polygon){
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
  std::vector<Polygon> getPolygonsWithNumOfVertexes(const std::vector<Polygon> &polygons, std::size_t num)
  {
    using namespace std::placeholders;
    auto countVertexes = std::bind(isCountOfVertexes, _1, num);
    std::vector<Polygon> result;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(result), countVertexes);
    return result;
  }
}