#ifndef COMMANDS_LIST_HPP
#define COMMANDS_LIST_HPP

#include "commands.hpp"

namespace turkin
{
  func_t main_list
  {
    {"ADD", add},
    {"REMOVE", remove},
    {"FIND", find},
    {"COUNT", count},
    {"SAVE", save},
    {"HELP", help}
  };
}
#endif
