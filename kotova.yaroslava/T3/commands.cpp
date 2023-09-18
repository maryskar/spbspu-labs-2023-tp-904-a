#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include <stdexcept>
#include "iofmtguard.hpp"

namespace kotova
{
  bool isEven(const Polygon &polygon)
  {
    return polygon.points.size() % 2 ==0;
  }
  bool isOdd(const Polygon &polygon)
  {
    return !isEven(polygon);
  }
  bool calcNumVert(const Polygon &polygon, size_t cnt)
  {
    return polygon.points.size() == cnt;
  }
  
}
