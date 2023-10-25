#ifndef T3_COMMANDS_H
#define T3_COMMANDS_H
#include <istream>
#include <vector>
#include "polygon.h"
namespace timofeev
{
  void doAreaCommands(std::istream &in, const std::vector< Polygon >& res);
  void doMaxCommands(std::istream &in, const std::vector< Polygon >& res);
  void doMinCommands(std::istream &in, const std::vector< Polygon >& res);
  void doCountCommands(std::istream &in, const std::vector< Polygon >& res);
  void doRectsCommand(std::istream&, const std::vector< Polygon >& res);
  void doRSCommand(std::istream&, const std::vector< Polygon >& res);
}
#endif
