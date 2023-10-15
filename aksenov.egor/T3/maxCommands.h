#ifndef MAXCOMMANDS_H
#define MAXCOMMANDS_H
#include <vector>
#include "polygon.h"

namespace aksenov
{
  void doMaxArea(const std::vector< Polygon > &pol);
  void doMaxVertexes(const std::vector< Polygon > &pol);
}
#endif
