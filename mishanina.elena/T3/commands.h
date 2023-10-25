#ifndef COMMANDS_H
#define COMMANDS_H
#include "Polygon.h"
#include <iomanip>

namespace mishanina
{
  void printAreaEven(const std::vector< Polygon > &polygons, std::ostream &out);
  void printAreaOdd(const std::vector< Polygon > &polygons, std::ostream &out);
  void printAreaMean(const std::vector< Polygon > &polygons, std::ostream &out);
  void printAreaNumOfVertexes(const std::vector< Polygon > &polygons, std::ostream &out, std::size_t num);
  void printMaxArea(const std::vector< Polygon > &polygons, std::ostream &out);
  void printMaxVertexes(const std::vector< Polygon > &polygons, std::ostream &out);
  void printMinArea(const std::vector< Polygon > &polygons, std::ostream &out);
  void printMinVertexes(const std::vector< Polygon > &polygons, std::ostream &out);
  void printCountEven(const std::vector< Polygon > &polygons, std::ostream &out);
  void printCountOdd(const std::vector< Polygon > &polygons, std::ostream &out);
  void printCountNumOfVertexes(const std::vector< Polygon > &polygons, std::ostream &out, std::size_t num);
  void printRects(const std::vector< Polygon > &polygons, std::ostream &out);
  void printRmecho(std::vector< Polygon > &polygons, std::ostream &out, std::istream &in);
}
#endif
