#ifndef SPBSPU_LABS_2023_TP_904_A_COMMANDS_H
#define SPBSPU_LABS_2023_TP_904_A_COMMANDS_H
#include <deque>
#include "polygon.h"
namespace avdeeva
{
  double calcAreaOdd(const std::deque< Polygon > & polygons);
  double calcAreaEven(const std::deque< Polygon > & polygons);
  double calcAreaMean(const std::deque< Polygon > & polygons);
  double calcAreaVerts(const std::deque< Polygon > & polygons, size_t num);
  size_t countEven(const std::deque< Polygon > & polygons);
  size_t countOdd(const std::deque< Polygon > & polygons);
  size_t countIsNumVertexes(const std::deque< Polygon > & polygons, size_t num);
  double findMaxArea(const std::deque< Polygon > & polygons);
  size_t findMaxVerts(const std::deque< Polygon > & polygons);
  double findMinArea(const std::deque< Polygon > & polygons);
  size_t findMinVerts(const std::deque< Polygon > & polygons);
  size_t countRightShapes(const std::deque< Polygon > & polygons);
  bool isInFrame(const std::deque< Polygon > & polygons, const Polygon & polygon);
}
#endif
