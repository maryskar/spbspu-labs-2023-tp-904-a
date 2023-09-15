#ifndef T3_COMMANDS_H
#define T3_COMMANDS_H
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "polygon.h"

namespace mashkin
{
  void runArea(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res);
  void runMax(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res);
  void runRightShapes(std::istream&, std::ostream& out, const std::deque< Polygon >& res);
  void runPerms(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res);
  void runCount(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res);
  void runMin(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res);
}
#endif
