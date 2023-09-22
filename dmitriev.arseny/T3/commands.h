#ifndef COMMANDS
#define COMMANDS

#include "polygon.h"

namespace dmitriev
{
  void printEvenArea(std::vector< Polygon > data, std::ostream& out);
  void printOddArea(std::vector< Polygon > data, std::ostream& out);
  void printNSizeArea(std::vector< Polygon > data, size_t number, std::ostream& out);
  void printMeanArea(std::vector< Polygon > data, std::ostream& out);
  void printMaxArea(std::vector< Polygon > data, std::ostream& out);


}

#endif
