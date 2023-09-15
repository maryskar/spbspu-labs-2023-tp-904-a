#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <functional>
#include <map>
#include <deque>
#include "polygon.hpp"
#include "sub_commands.hpp"

namespace zhuravlev
{
  using const_cmd_t = std::function< void (const std::vector< Polygon >&, std::ostream& ) >;
  using cmd_t = std::function< void (std::deque< Polygon >&, std::istream&, std::ostream&, std::ostream&) >;
  std::map< std::string, const_cmd_t > const_cmds
  {
    {"COUNT ODD", countOdd},
    {"COUNT EVEN", countEven}
  };
}
#endif
