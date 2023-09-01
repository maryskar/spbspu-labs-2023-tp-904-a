#ifndef FA_DO_COMMAND_HPP
#define FA_DO_COMMAND_HPP
#include "create-commands-maps.hpp"

namespace chemodurov
{
  std::string readCommand(std::istream & in);
  void doCommandFromMaps(const std::string & name_cmd,
      const CommandsMaps & cmds,
      std::istream & in,
      std::ostream & out,
      DictWithFreqDicts & data);
}

#endif
