#ifndef COMMANDS_H
#define COMMANDS_H
#include "polygon.h"

namespace skarlygina
{
  void findEvenOddArea(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void findMeanArea(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void findAreaPoints(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void findMax(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void findMin(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void countFigures(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void findPerms(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void findSame(const std::vector< Polygon >&, std::istream&, std::ostream&);
}

#endif

