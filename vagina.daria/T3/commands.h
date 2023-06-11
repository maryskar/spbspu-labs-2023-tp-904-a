#ifndef T3_COMMANDS_H
#define T3_COMMANDS_H
#include "polygon.h"

namespace vagina
{
  void areaEven(const std::vector< Polygon >& dest, std::ostream& out);
  void areaOdd(const std::vector< Polygon >& dest, std::ostream& out);
  void areaMean(const std::vector< Polygon >& dest, std::ostream& out);
  void areaVertexes(const std::vector< Polygon >& dest, std::ostream& out, std::size_t param);
  void maxArea(const std::vector < Polygon >& dest, std::ostream& out);
  void maxVertexes(const std::vector < Polygon >& dest, std::ostream& out);
  void minArea(const std::vector < Polygon >& dest, std::ostream& out);
  void minVertexes(const std::vector < Polygon >& dest, std::ostream& out);
  void countEven(const std::vector < Polygon >& dest, std::ostream& out);
  void countOdd(const std::vector < Polygon >& dest, std::ostream& out);
  void countVertexes(const std::vector < Polygon >& dest, std::ostream& out, std::size_t param);
  bool isEven(const Polygon & pol);
  bool isCountOfVertexes(const Polygon& pol, std::size_t param);
  void messageInvalidCommand(std::ostream& out);
}


#endif
