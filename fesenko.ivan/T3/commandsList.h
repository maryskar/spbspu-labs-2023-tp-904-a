#ifndef COMMANDSLIST_H
#define COMMANDSLIST_H
#include <map>
#include "commands.h"
namespace fesenko
{
  using main_cmd_t = std::ostream &(*)(data_t &, std::istream &, std::ostream &);
  std::map<std::string, main_cmd_t > main_list
  {
    {"AREA", area},
    {"MAX", max},
    {"MIN", min},
    {"COUNT", count},
    {"RECTS", rects},
    {"INFRAME", inframe}
  };
}
#endif
