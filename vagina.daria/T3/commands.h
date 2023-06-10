#ifndef T3_COMMANDS_H
#define T3_COMMANDS_H
#include "polygon.h"

namespace vagina
{
  void areaEven(const std::vector< Polygon >& dest, std::ostream& out);
  void areaOdd(const std::vector< Polygon >& dest, std::ostream& out);
  bool isEven(const Polygon & pol);
}


#endif
