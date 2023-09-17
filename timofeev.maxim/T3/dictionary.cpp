#include "dictionary.h"
#include "commands.h"
namespace timofeev
{
  void dictionary(dict& command)
  {
    command["AREA"] = doAreaCommands;
    command["MAX"] = doMaxCommands;
    command["MIN"] = doMinCommands;
    command["COUNT"] = doCountCommands;
    command["RECTS"] = doRectsCommand;
    command["RIGHTSHAPES"] = doRSCommand;
  }
}
