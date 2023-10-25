#ifndef COMMANDS_H
#define COMMANDS_H
#include "polygon.h"

namespace skarlygina
{
  void getArea(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void getMax(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void getMin(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void countFigures(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void findPerms(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void findSame(const std::vector< Polygon >&, std::istream&, std::ostream&);
  std::ostream& printInvalidCommand(std::ostream&);
}

#endif

