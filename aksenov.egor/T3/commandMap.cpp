#include "commandMap.h"
#include "commands.h"

namespace aksenov
{
  commandMap makeDict()
  {
    commandMap commands;
    commands["AREA"] = doArea;
    commands["MAX"] = doMax;
    commands["MIN"] = doMin;
    commands["COUNT"] = doCount;
    commands["SAME"] = doSame;
    commands["RIGHTSHAPES"] = doRightshapes;
    return commands;
  }
}
