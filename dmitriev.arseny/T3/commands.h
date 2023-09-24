#ifndef COMMANDS_H
#define COMMANDS_H

#include "polygon.h"

using polygon = dmitriev::Polygon;
using polygons = std::vector< polygon >;

namespace dmitriev
{
  void printEvenArea(const polygons& data, std::ostream& out);
  void printOddArea(const polygons& data, std::ostream& out);
  void printNSizeArea(const polygons& data, size_t number, std::ostream& out);
  void printMeanArea(const polygons& data, std::ostream& out);
  void printMaxArea(const polygons& data, std::ostream& out);
  void printMinArea(const polygons& data, std::ostream& out);
  void printMaxSize(const polygons& data, std::ostream& out);
  void printMinSize(const polygons& data, std::ostream& out);
  void printEvenSizeCount(const polygons& data, std::ostream& out);
  void printOddSizeCount(const polygons& data, std::ostream& out);
  void printNSizeCount(const polygons& data, size_t number, std::ostream& out);
  void printInFrame(const polygons& data, const polygon& figure, std::ostream& out);
  void printSame(const polygons& data, const polygon& figure, std::ostream& out);
}

#endif
