#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <functional>
#include <map>
#include <deque>
#include "polygon.hpp"

namespace zhuravlev
{
  using const_cmd_t = std::function< void (const std::deque< Polygon >&, std::istream&, std::ostream&, std::ostream&) >;
  using cmd_t = std::function< void (std::deque< Polygon >&, std::istream&, std::ostream&, std::ostream&) >;
  
}
#endif
