#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include "polygon.h"

namespace aristarkhov
{
  size_t getVerticesCount(const Polygon& polygon);
  double getArea(const Polygon& polygon);

  void countOdd(const std::vector< Polygon >& polygons, std::ostream& out);
  void countEven(const std::vector< Polygon >& polygons, std::ostream& out);

  void areaEven(const std::vector< Polygon >& polygons, std::ostream& ostream);
  void areaOdd(const std::vector< Polygon >& polygons, std::ostream& ostream);
  void areaMean(const std::vector< Polygon >& polygons, std::ostream& ostream);
  void areaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);

  void minArea(const std::vector< Polygon >& polygons, std::ostream& ostream);
  void maxArea(const std::vector< Polygon >& polygons, std::ostream& ostream);

  void maxVertexes(const std::vector< Polygon >& polygons, std::ostream& ostream);
  void minVertexes(const std::vector< Polygon >& polygons, std::ostream& ostream);

  void countVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& ostream);
  void rmEcho(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& ostream);

  using Frame = std::pair< Point, Point >;
  void printInFrame(std::vector< Polygon >& polygons, const Polygon& figure, std::ostream& out);
}

#endif
