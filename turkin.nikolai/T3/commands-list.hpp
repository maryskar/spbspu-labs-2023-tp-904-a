#ifndef COMMANDS_LIST_HPP
#define COMMANDS_LIST_HPP

#include <map>

#include "commands.hpp"

namespace turkin
{
  using main_cmd_t = std::ostream & (*)(data_t &, std::istream &, std::ostream &);
  std::map< std::string, main_cmd_t > main_list
  {
    {"AREA", area},
    {"MAX", max},
    {"MIN", min},
    {"COUNT", count},
    {"MAXSEQ", maxseq},
    {"RIGHTSHAPES", rightshapes}
  };
}
#endif
