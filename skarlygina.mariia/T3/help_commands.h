#ifndef HELP_COMMANDS_H
#define HELP_COMMANDS_H
#include "polygon.h"
namespace skarlygina
{
  double findAreaPoly(const skarlygina::Polygon&, double area = 0.0);
  double findAreaOdd(const std::vector< Polygon >&);
  double findAreaEven(const std::vector< Polygon >&);
  double findAreaMean(const std::vector< Polygon >&);
  double findAreaNumOfVertexes(const std::vector< Polygon >&, size_t);

  double maxArea(const std::vector< Polygon >&);
  size_t maxVertexes(const std::vector< Polygon >&);
  double minArea(const std::vector< Polygon >&);
  size_t minVertexes(const std::vector< Polygon >&);

  size_t countOdd(const std::vector< Polygon >&);
  size_t countEven(const std::vector< Polygon >&);
  size_t countNumOfVertexes(const std::vector< Polygon >&, size_t);

  bool isSame(const skarlygina::Polygon&, const skarlygina::Polygon&);
  bool isPerm(const skarlygina::Polygon&, const skarlygina::Polygon&);
}

#endif
