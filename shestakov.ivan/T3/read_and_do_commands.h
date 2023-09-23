#ifndef UNTITLED3_READ_AND_DO_COMMANDS_H
#define UNTITLED3_READ_AND_DO_COMMANDS_H
#include <iostream>
#include <vector>
#include "polygon.h"

namespace shestakov
{
  std::string readCommand(std::istream& in);
  void doCommand(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out, std::string cmd);
  void doConstCmds(const std::vector< Polygon >& polygons, std::ostream& out, const std::string& cmd);
  void doConstCmdsIn(const std::vector< Polygon >& polygons, std::ostream& out, std::string cmd);
  void doCmdsWithInPolygon(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out, const std::string& cmd);
}
#endif
