#ifndef UNTITLED3_AUXILIARY_COMMANDS_H
#define UNTITLED3_AUXILIARY_COMMANDS_H
#include "polygon.h"

namespace shestakov
{
  void printError(std::ostream& out);
  void skipUntilNewLine(std::istream &in);
  bool isEven(const Polygon& polygons);
  bool isOdd(const Polygon& polygons);
  size_t countVertexes(const Polygon& polygon);
  std::ostream& printFix(double src, std::ostream& out);
  int getDeter(const Point& first, const Point& second);
  double getArea(const Polygon& polygons);
  bool equalVert(const Polygon& polygon, size_t vert);
  bool compTwoPolygons(const Polygon& polygon_1, const Polygon& polygon_2);
  bool compThreePolygons(const Polygon& polygon_1, const Polygon& polygon_2, const Polygon& polygon_3);
}
#endif
