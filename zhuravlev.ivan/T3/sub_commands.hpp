#ifndef SUB_COMMANDS_HPP
#define SUB_COMMANDS_HPP
#include <iterator>
#include "polygon.hpp"

namespace zhuravlev
{
  size_t getNumberOfVertexes(const Polygon& polygon);
  bool isCountOfVertexes(const Polygon& polygon, const size_t num_of_vertexes);
  double getSide(const Point& lhs, const Point& rhs);
  double getArea(const Polygon& polygons);
  bool isEven(const Polygon& polygons);
  bool isOdd(const Polygon& polygons);
  void countOdd(const std::vector< zhuravlev::Polygon >& polygons, std::ostream& out);
  void countEven(const std::vector< zhuravlev::Polygon >& polygons, std::ostream& out);
  void countVertexes(const std::vector< Polygon >& polygons, std::ostream& out, const size_t condition);
  void AreaEven(const std::vector< zhuravlev::Polygon >& polygons, std::ostream& out);
  void AreaOdd(const std::vector< zhuravlev::Polygon >& polygons, std::ostream& out);
  void AreaMean(const std::vector< zhuravlev::Polygon >& polygons, std::ostream& out);
  void AreaVertexes(const std::vector< zhuravlev::Polygon >& polygons, std::ostream& out, const size_t condition);
  void MaxArea(const std::vector< zhuravlev::Polygon >& polygons, std::ostream& out);
  void MaxVertexes(const std::vector< zhuravlev::Polygon >& polygons, std::ostream& out);
  void MinArea(const std::vector< zhuravlev::Polygon >& polygons, std::ostream& out);
  void MinVertexes(const std::vector< zhuravlev::Polygon >& polygons, std::ostream& out);
  void inFrame(const std::vector< zhuravlev::Polygon >& polygons, std::istream& in, std::ostream& out);
  void rmEcho(std::vector< zhuravlev::Polygon >& polygons, std::istream& in, std::ostream& out);
  void printError(std::ostream& out);
}
#endif
