#ifndef T3_MAPWITHCOMMANDS_H
#define T3_MAPWITHCOMMANDS_H
#include <deque>
#include <map>
#include <string>
#include <vector>
#include "polygon.h"

namespace mashkin
{
  std::map< std::string, std::ostream& (*)(std::istream&,
      std::ostream&,
      const std::deque< Polygon>&) > createMapWithCommands();
}
#endif
