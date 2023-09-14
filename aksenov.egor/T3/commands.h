#ifndef COMMANDS_H
#define COMMANDS_H
#include <vector>
#include <iostream>
#include "polygon.h"
namespace aksenov
{
  void doArea(std::istream &inp, const std::vector< Polygon > &pol, std::ostream &);
  void doMax(std::istream &inp, const std::vector< Polygon > &pol, std::ostream &);
  void doMin(std::istream &inp, const std::vector< Polygon > &pol, std::ostream &);
  void doCount(std::istream &inp, const std::vector< Polygon >&pol, std::ostream &);
  void doSame(std::istream &inp, const std::vector< Polygon > &pol, std::ostream &);
  void doRightshapes(std::istream &, const std::vector< Polygon > &pol, std::ostream &);
}
#endif
