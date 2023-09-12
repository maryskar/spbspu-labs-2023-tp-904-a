#ifndef COMMANDS_H
#define COMMANDS_H
#include <map>
#include "datastructs.h"

namespace azheganova
{
  using str = std::string;
  using vec = std::vector< Polygon >;
  bool isEven(const Polygon & polygon);
  bool isOdd(const Polygon & polygon);
  void getAreaEven(std::vector< Polygon > & polygon, std::ostream & out);
  void getAreaOdd(std::vector< Polygon > & polygon, std::ostream & out);
  void getAreaMean(std::vector< Polygon > & polygon, std::ostream & out);
  double isCountVertex(const Polygon & polygon, size_t vertexcount);
  void getAreaNumOfVertexes(std::vector< Polygon > & polygon, size_t num, std::ostream & out);
  void getMaxArea(std::vector< Polygon > & polygon, std::ostream & out);
  void getMaxVertexes(std::vector< Polygon > & polygon, std::ostream & out);
  void getMinArea(std::vector< Polygon > & polygon, std::ostream & out);
  void getMinVertexes(std::vector< Polygon > & polygon, std::ostream & out);
  void countEven(std::vector< Polygon > & polygon, std::ostream & out);
  void countOdd(std::vector< Polygon > & polygon, std::ostream & out);
  void countNumOfVertexes(std::vector< Polygon > & polygon, size_t num, std::ostream & out);
  bool isCompareRmecho(const Polygon & first, const Polygon & second, const Polygon & polygon);
  void getRmecho(std::vector< Polygon > & polygon, std::ostream & out, std::istream & in);
  void getRightshapes(std::vector< Polygon > & polygon, std::ostream & out);
  std::string inputCommand(std::istream & in);
  std::ostream & printInvalidCommand(std::ostream & out);
}

#endif
