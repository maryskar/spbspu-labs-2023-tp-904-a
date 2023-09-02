#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <deque>
#include <istream>
#include <ostream>

#include "data-structs.hpp"

namespace turkin
{
  using data_t = std::deque< Polygon >;
  std::ostream & area(data_t & data, std::istream & in, std::ostream & out);
  std::ostream & min(data_t & data, std::istream & in, std::ostream & out);
  std::ostream & max(data_t & data, std::istream & in, std::ostream & out);
  std::ostream & count(data_t & data, std::istream & in, std::ostream & out);
  std::ostream & maxseq(data_t & data, std::istream & in, std::ostream & out);
  std::ostream & rightshapes(data_t & data, std::istream & in, std::ostream & out);
}

#endif
