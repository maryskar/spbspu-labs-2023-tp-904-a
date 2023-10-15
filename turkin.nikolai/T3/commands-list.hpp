#ifndef COMMANDS_LIST_HPP
#define COMMANDS_LIST_HPP

#include <map>

#include "commands.hpp"

namespace turkin
{
  using main_cmd_t = ReturnType (*)(data_t &, SubCommandsList &, std::string &, std::string &);
  using main_map_t = std::map< std::string, main_cmd_t >;
  struct CommandsList
  {
    public:
      CommandsList();
      main_cmd_t & get(const std::string & type);
    private:
       main_map_t list_;
  };
}
#endif
