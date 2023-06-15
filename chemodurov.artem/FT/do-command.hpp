#ifndef FA_DO_COMMAND_HPP
#define FA_DO_COMMAND_HPP
#include <read-and-do-command.hpp>
#include "create-commands-maps.hpp"

namespace chemodurov
{
  void doCommandFromMaps(const std::string & name_cmd,
      const CommandsMaps & cmds,
      std::istream & in,
      std::ostream & out,
      DictWithFreqDicts & data);
}

#endif
