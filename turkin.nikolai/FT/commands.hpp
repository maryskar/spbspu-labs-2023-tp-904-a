#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "data-types.hpp"

namespace turkin
{
  std::ostream & add(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & remove(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & find(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & count(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & save(base_t & base, std::istream & in, std::ostream & out);
  std::ostream & help(base_t & base, std::istream & in, std::ostream & out);
}

#endif
