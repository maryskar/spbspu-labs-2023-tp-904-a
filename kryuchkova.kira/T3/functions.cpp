#include "functions.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include <iomanip>
#include "polygon.h"

namespace kryuchkova
{
  bool isEven(const Polygon & polygon)
  {
    return !(polygon.points.size() % 2);
  }

  bool isOdd(const Polygon & polygon)
  {
    return !(isEven(polygon));
  }

  bool isEqualNum(const Polygon & polygon, size_t num)
  {
    return polygon.points.size() == num;
  }

  bool isLessArea(const Polygon & lhs, const Polygon & rhs)
  {
    return getArea(lhs) < getArea(rhs);
  }

  bool isLessVer(const Polygon & lhs, const Polygon & rhs)
  {
    return lhs.points.size() < rhs.points.size();
  }

  
}