#ifndef FT_COMMANDS_HPP
#include <iosfwd>
#include "helpFunctions.hpp"

namespace malaya
{
  void info(std::ostream & out);
  void deleteKey(dictionary &, const std::string & key, std::ostream & out);
}
#define FT_COMMANDS_HPP
#endif
