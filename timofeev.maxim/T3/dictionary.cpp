#include "dictionary.h"
#include "commands.h"
timofeev::dict timofeev::setDictionary()
{
  timofeev::dict command;
  command["AREA"] = doAreaCommands;
  command["MAX"] = doMaxCommands;
  command["MIN"] = doMinCommands;
  command["COUNT"] = doCountCommands;
  command["RECTS"] = doRectsCommand;
  command["RIGHTSHAPES"] = doRSCommand;
  return command;
}
