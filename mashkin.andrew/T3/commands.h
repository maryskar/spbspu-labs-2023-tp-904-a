#ifndef T3_COMMANDS_H
#define T3_COMMANDS_H
#include <iostream>
#include <string>
#include <vector>
#include "polygon.h"

namespace mashkin
{
  void runCommand(std::istream& inp, std::string& command, const std::vector< Polygon >& res);
}
#endif
