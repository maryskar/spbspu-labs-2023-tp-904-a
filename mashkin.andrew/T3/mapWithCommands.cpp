#include "mapWithCommands.h"
#include <map>
#include <string>
#include "polygon.h"
#include "commands.h"

namespace mashkin
{
  using commandMap = std::map< std::string, void (*)(std::istream&, std::ostream&, const std::deque< Polygon>&) >;
  commandMap createMapWithCommands()
  {
    commandMap commands;
    commands["AREA"] = runArea;
    commands["MAX"] = runMax;
    commands["MIN"] = runMin;
    commands["COUNT"] = runCount;
    commands["PERMS"] = runPerms;
    commands["RIGHTSHAPES"] = runRightshapes;
    return commands;
  }
}
