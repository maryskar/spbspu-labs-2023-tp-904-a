#include "dictionary.h"
#include "commands.h"
namespace timofeev
{
  dict dictionary(dict& command)
  {
    command["AREA"] = doAreaCommands;
    command["MAX"] = doMaxCommands;
    command["MIN"] = doMinCommands;
    command["COUNT"] = doCountCommands;
    command["RECTS"] = doRectsCommand;
    command["RIGHTSHAPES"] = doRSCommand;
    return command;
  }
}
