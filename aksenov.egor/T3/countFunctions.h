#ifndef COUNTFUNCTIONS_H
#define COUNTFUNCTIONS_H
#include <vector>
#include "polygon.h"

namespace aksenov
{
  void doCountEven(const std::vector< Polygon > &pol);
  void doCountOdd(const std::vector< Polygon > &pol);
  void doCountVertexes(std::string command, const std::vector< Polygon > &pol);
}
#endif
