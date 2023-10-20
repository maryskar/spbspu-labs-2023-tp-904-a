#include "commands-list.hpp"

turkin::CommandsList::CommandsList():
  list_({
    {"AREA", area},
    {"MAX", max},
    {"MIN", min},
    {"COUNT", count},
    {"MAXSEQ", maxseq},
    {"RIGHTSHAPES", rightshapes}
  })
{}

turkin::main_cmd_t & turkin::CommandsList::get(const std::string & type)
{
  return list_.at(type);
}
