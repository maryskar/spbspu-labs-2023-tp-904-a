#ifndef COMMANDS_H
#define COMMANDS_H

#include "polygon.h"

using polygon = dmitriev::Polygon;
using polygons = std::vector< polygon >;

namespace dmitriev
{
  void printEvenArea(polygons data, std::ostream& out);
  void printOddArea(polygons data, std::ostream& out);
  void printNSizeArea(polygons data, size_t number, std::ostream& out);
  void printMeanArea(polygons data, std::ostream& out);
  void printMaxArea(polygons data, std::ostream& out);
  void printMinArea(polygons data, std::ostream& out);
  void printMaxSize(polygons data, std::ostream& out);
  void printMinSize(polygons data, std::ostream& out);
  void printEvenSizeCount(polygons data, std::ostream& out);
  void printOddSizeCount(polygons data, std::ostream& out);
  void printNSizeCount(polygons data, size_t number, std::ostream& out);

  void printInFrame(const polygons& data, const polygon& figure, std::ostream& out);
  void printSame(const polygons& data, const polygon& figure, std::ostream& out);
}

#endif
