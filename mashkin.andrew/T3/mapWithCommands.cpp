#include "mapWithCommands.h"
#include <map>
#include <string>
#include "polygon.h"
#include "commands.h"

namespace mashkin
{
  void createMapWithCommands(commandMap& commands)
  {
    commands["AREA"] = runArea;
    commands["MAX"] = runMax;
    commands["MIN"] = runMin;
    commands["COUNT"] = runCount;
    commands["PERMS"] = runPerms;
    commands["RIGHTSHAPES"] = runRightshapes;
  }
}
