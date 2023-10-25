#ifndef UNTITLED3_COMMANDS_H
#define UNTITLED3_COMMANDS_H
#include "polygon.h"

namespace shestakov
{
  void areaEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void areaOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void areaMean(const std::vector< Polygon >& polygons, std::ostream& out);
  void maxArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void minArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void maxVertexes(const std::vector< Polygon >& polygons, std::ostream& out);
  void minVertexes(const std::vector< Polygon >& polygons, std::ostream& out);
  void countEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void countOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void countVert(const std::vector< Polygon >& polygons, size_t num, std::ostream& out);
  void areaVert(const std::vector< Polygon >& polygons, size_t num, std::ostream& out);
  void rmecho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void echo(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
}
#endif
