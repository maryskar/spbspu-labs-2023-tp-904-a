#ifndef MINCOMMANDS_H
#define MINCOMMANDS_H
#include <vector>
#include "polygon.h"
namespace aksenov
{
  void doMinArea(const std::vector< Polygon > &pol);
  void doMinVertexes(const std::vector< Polygon > &pol);
}
#endif
