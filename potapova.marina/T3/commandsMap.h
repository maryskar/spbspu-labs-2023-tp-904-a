#ifndef COMMANDSMAP_H
#define COMMANDSMAP_H

#include <unordered_map>
#include <functional>
#include <string>
#include "commandsMapsAliases.h"

namespace potapova
{
  NotChangingCommansMap getNonChangingCommands();
  ChangingCommansMap getChangingCommands();
}

#endif
