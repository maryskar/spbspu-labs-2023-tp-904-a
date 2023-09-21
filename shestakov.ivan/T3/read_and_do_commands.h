#ifndef UNTITLED3_READ_AND_DO_COMMANDS_H
#define UNTITLED3_READ_AND_DO_COMMANDS_H
#include <iostream>
#include <vector>
#include "polygon.h"

namespace shestakov
{
  void doCommand(std::vector< Polygon >&, std::istream& in, std::ostream& out, std::string cmd);
  void doConstCmds(const std::vector< Polygon >& polygons, std::ostream& out, std::string cmd);
  void doConstCmdsIn(const std::vector< Polygon >& polygons, size_t vertexes, std::ostream& out, std::string cmd);
  void doCmdsWithInPolygon(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out, std::string cmd);
}
#endif
