#ifndef UNTITLED3_COMMANDS_H
#define UNTITLED3_COMMANDS_H
#include "polygon.h"

namespace shestakov
{
  bool isEven(const Polygon& polygons);
  bool isOdd(const Polygon& polygons);
  size_t countVertexes(const Polygon& polygon);
  double getDeterminant(const Point& first, const Point& second);
  double getArea(const Polygon& polygons);
  bool equalVert(const Polygon& polygon, const size_t vert);
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
  void printError(std::ostream& out);
}
#endif
