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
}