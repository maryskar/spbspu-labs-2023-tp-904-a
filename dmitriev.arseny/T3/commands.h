#ifndef COMMANDS
#define COMMANDS

#include "polygon.h"

namespace dmitriev
{
  void printEvenArea(std::ostream& out, std::vector< Polygon > data);
  void printOddArea(std::ostream& out, std::vector< Polygon > data);
  void printNSizeArea(std::ostream& out, std::vector< Polygon > data, size_t number);

   
}

#endif
