#ifndef T3_COMMANDS_H
#define T3_COMMANDS_H
#include <iostream>
#include <string>
#include <vector>
#include "polygon.h"

namespace mashkin
{
  using pol = Polygon;
  using vecPol = std::vector< pol >;
  void runArea(std::istream& inp, const vecPol& res);
  void runMax(std::istream& inp, const vecPol& res);
  void runRightshapes(std::istream&, const vecPol& res);
  void runPerms(std::istream& inp, const vecPol& res);
  void runCount(std::istream& inp, const vecPol& res);
  void runMin(std::istream& inp, const vecPol& res);
}
#endif
