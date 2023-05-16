#include "commandFunctions.hpp"
#include "helpFunctions.hpp"

namespace malaya
{
  double areaEven(const Polygon & polygon)
  {
    return (polygon.points.size() % 2 ? 0.0 : getArea(polygon));
  }
  double areaOdd(const Polygon & polygon)
  {
    return (polygon.points.size() % 2 ? getArea(polygon) : 0.0);
  }
  double areaNum(const Polygon & polygon, size_t num)
  {
    return (polygon.points.size() == num ? getArea(polygon) : 0.0);
  }
  template < typename Predicate >
  double minMaxArea(std::vector< malaya::Polygon > data)
  {

  }
  double maxArea(std::vector< malaya::Polygon > data)
  {

  }
}