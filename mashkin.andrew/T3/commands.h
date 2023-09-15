#ifndef T3_COMMANDS_H
#define T3_COMMANDS_H
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "polygon.h"

namespace mashkin
{
  std::ostream& runArea(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res);
  std::ostream& runMax(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res);
  std::ostream& runRightShapes(std::istream&, std::ostream& out, const std::deque< Polygon >& res);
  std::ostream& runPerms(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res);
  std::ostream& runCount(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res);
  std::ostream& runMin(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res);
}
#endif
