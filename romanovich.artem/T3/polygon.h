#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <algorithm>
#include "pointutils.h"
namespace romanovich
{
  struct Polygon
  {
    std::vector< Point > points;
  };
}
#endif
