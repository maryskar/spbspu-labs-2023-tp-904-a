#ifndef AREA_TYPE
#define AREA_TYPE

#include "point-struct.hpp"
#include <vector>
namespace turkin
{
  double calcArea(const Polygon & rhs);
  double oddArea(double in, const Polygon & rhs);
  double evenArea(double in, const Polygon & rhs);
  double numArea(double in, const Polygon & rhs);
}

#endif
