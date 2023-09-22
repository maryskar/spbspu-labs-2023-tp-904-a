#ifndef COMMANDS
#define COMMANDS

#include "polygon.h"

namespace dmitriev
{
  std::ostream& printEvenArea(std::ostream& out, std::vector< Polygon > data);
  std::ostream& printOddArea(std::ostream& out, std::vector< Polygon > data);
  std::ostream& printNSizeArea(std::ostream& out, std::vector< Polygon > data, size_t number);

   
}

#endif
