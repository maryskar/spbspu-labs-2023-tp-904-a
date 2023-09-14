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
}
#endif
