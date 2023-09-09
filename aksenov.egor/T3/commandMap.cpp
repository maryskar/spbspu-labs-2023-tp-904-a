#include "commandMap.h"
#include <commands.h>
namespace aksenov
{
  void makeDict(commandMap &commands)
  {
    commands["AREA"] = doArea;
    commands["MAX"] = doMax;
    commands["MIN"] = doMin;
    commands["COUNT"] = doCount;
    commands["SAME"] = doSame;
    commands["RIGHTSHAPES"] = doRightshapes;
  }
}