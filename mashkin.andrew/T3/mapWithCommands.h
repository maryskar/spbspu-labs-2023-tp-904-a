#ifndef T3_MAPWITHCOMMANDS_H
#define T3_MAPWITHCOMMANDS_H
#include <map>
#include <string>
#include <vector>
#include "polygon.h"

namespace mashkin
{
  using vec = std::vector< Polygon >;
  using commandMap = std::map< std::string, void (*)(std::istream&, const vec&) >;
  commandMap createMapWithCommands();
}
#endif
