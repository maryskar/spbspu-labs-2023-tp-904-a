#ifndef COMMANDS_H
#define COMMANDS_H
#include "Polygon.h"
#include <iomanip>
#include "extra_commands.h"
namespace mishanina{
  void printAreaEven(const std::vector<Polygon>& polygons, std::ostream& out);
  void printAreaOdd(const std::vector<Polygon>& polygons, std::ostream& out);
  void printAreaMean(const std::vector<Polygon>& polygons, std::ostream& out);
  void printAreaNumOfVertexes(const std::vector<Polygon> &polygons, std::ostream &out, std::size_t num);
  void printMaxArea(const std::vector<Polygon> &polygons, std::ostream &out);
  void printMaxVertexes(const std::vector<Polygon> &polygons, std::ostream &out);
  void printMinArea(const std::vector<Polygon> &polygons, std::ostream &out);
  void printMinVertexes(const std::vector<Polygon> &polygons, std::ostream &out);

}
#endif
