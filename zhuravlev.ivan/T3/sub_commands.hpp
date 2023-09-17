#ifndef SUB_COMMANDS_HPP
#define SUB_COMMANDS_HPP
#include "polygon.hpp"

namespace zhuravlev
{
  size_t getNumberOfVertexes(const Polygon& polygon);
  bool isCountOfVertexes(const Polygon& polygon, const size_t num_of_vertexes);
  double getSide(const Point& lhs, const Point& rhs);
  double getArea(const Polygon& polygons);
  bool isEven(const Polygon& polygons);
  bool isOdd(const Polygon& polygons);
  void countOdd(const std::vector< zhuravlev::Polygon >& polygons, std::istream&, std::ostream& out);
  void countEven(const std::vector< zhuravlev::Polygon >& polygons, std::istream&, std::ostream& out);
  void countVertexes(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void AreaEven(const std::vector< zhuravlev::Polygon >& polygons, std::istream&, std::ostream& out);
  void AreaOdd(const std::vector< zhuravlev::Polygon >& polygons, std::istream&, std::ostream& out);
  void AreaMean(const std::vector< zhuravlev::Polygon >& polygons, std::istream&, std::ostream& out);
  void AreaVertexes(const std::vector< zhuravlev::Polygon >& polygons, std::istream& in, std::ostream& out);
  void MaxArea(const std::vector< zhuravlev::Polygon >& polygons, std::istream&, std::ostream& out);
  void MaxVertexes(const std::vector< zhuravlev::Polygon >& polygons, std::istream&, std::ostream& out);
  void MinArea(const std::vector< zhuravlev::Polygon >& polygons, std::istream&, std::ostream& out);
  void MinVertexes(const std::vector< zhuravlev::Polygon >& polygons, std::istream&, std::ostream& out);
  void printError(const std::vector< zhuravlev::Polygon >&, std::istream&, std::ostream& out);
}
#endif
