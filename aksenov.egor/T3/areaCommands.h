#ifndef AREACOMMANDS_H
#define AREACOMMANDS_H
#include "polygon.h"
#include <vector>

namespace aksenov
{
  void doAreaEven(const std::vector< Polygon > &pol);
  void doAreaOdd(const std::vector< Polygon > &pol);
  void doAreaMean(const std::vector< Polygon > &pol);
  void doAreaWithVertexes(const std::vector< Polygon > &pol, std::string command);
}
#endif
