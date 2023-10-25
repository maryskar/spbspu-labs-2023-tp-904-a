#ifndef COMMANDSMAP_H
#define COMMANDSMAP_H

#include <unordered_map>
#include <functional>
#include <string>
#include "commandsMapsAliases.h"

namespace potapova
{
  NotChangingCommandsMap getNonChangingCommands();
  ChangingCommandsMap getChangingCommands();
}

#endif
