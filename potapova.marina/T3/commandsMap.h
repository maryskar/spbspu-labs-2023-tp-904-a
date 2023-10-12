#ifndef COMMANDSMAP_H
#define COMMANDSMAP_H

#include <unordered_map>
#include "dataStruct.h"

namespace potapova
{
  using commandFunc = std::function< void(const std::deque< Polygon >&, std::istream&, std::ostream&, std::ostream&) >;

  std::unordered_map< std::string, commandFunc >
  extern non_changing_commands;

  std::unordered_map< std::string, commandFunc >
  extern changing_commands;
}

#endif
