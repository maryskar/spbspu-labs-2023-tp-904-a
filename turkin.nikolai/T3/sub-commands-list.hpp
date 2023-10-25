#ifndef SUB_COMMANDS_LIST_HPP
#define SUB_COMMANDS_LIST_HPP

#include <map>

#include "sub-commands.hpp"

namespace turkin
{
  using sub_cmd_t = ReturnType (*)(data_t & data, std::string &);
  using sub_inside_map_t = std::map< std::string, sub_cmd_t >;
  using sub_map_t = std::map< std::string, sub_inside_map_t >;
  struct SubCommandsList
  {
    public:
      SubCommandsList();
      sub_inside_map_t & get(const std::string & type);
    private:
      sub_map_t list_;
  };
}
#endif
