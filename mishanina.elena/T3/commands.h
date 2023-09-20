#ifndef COMMANDS_H
#define COMMANDS_H
#include "Polygon.h"
#include <iomanip>
#include "extra_commands.h"
namespace mishanina{
  void printAreaEven(const std::vector<Polygon>& polygons, std::ostream& out);
  void printAreaOdd(const std::vector<Polygon>& polygons, std::ostream& out);
  void printAreaMean(const std::vector<Polygon>& polygons, std::ostream& out);
}
#endif
