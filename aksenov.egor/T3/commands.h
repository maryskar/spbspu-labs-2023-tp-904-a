#ifndef COMMANDS_H
#define COMMANDS_H
#include <vector>
#include <iostream>
#include "polygon.h"
namespace aksenov
{
  void doArea(std::istream &inp, const std::vector< Polygon > &pol);
  void doMax(std::istream &inp, const std::vector< Polygon > &pol);
  void doMin(std::istream &inp, const std::vector< Polygon > &pol);
  void doCount(std::istream &inp, const std::vector< Polygon >&pol);
  void doSame(std::istream &inp, const std::vector< Polygon > &pol);
  void doRightshapes(std::istream &, const std::vector< Polygon > &pol);
}
#endif
