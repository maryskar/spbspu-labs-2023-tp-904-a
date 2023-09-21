#ifndef UNTITLED3_READ_AND_DO_COMMANDS_H
#define UNTITLED3_READ_AND_DO_COMMANDS_H
#include <iostream>
#include <vector>
#include "polygon.h"

namespace shestakov
{
  void doCommand(std::vector< Polygon >&, std::istream& in, std::ostream& out, std::string command);
  void doConstCommand(std::vector< Polygon >& pls, std::istream& in, std::ostream& out, std::string cmd);
  void doCommandWithInput(std::vector< Polygon >& pls, std::ostream& out, const size_t condition, std::string command);
  void doCommandWithInputPolygon(std::vector< Polygon >& pls, std::istream& in, std::ostream& out, std::string cmd);
}
#endif
