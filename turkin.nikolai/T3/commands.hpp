#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <ostream>
#include <vector>

#include "point-struct.hpp"

namespace turkin
{
  std::ostream & area(std::vector< Polygon > & data, std::istream & in, std::ostream & out);
  std::ostream & min(std::vector< Polygon > & data, std::istream & in, std::ostream & out);
  std::ostream & max(std::vector< Polygon > & data, std::istream & in, std::ostream & out);
  std::ostream & count(std::vector< Polygon > & data, std::istream & in, std::ostream & out);
  std::ostream & maxseq(std::vector< Polygon > & data, std::istream & in, std::ostream & out);
  std::ostream & rightshapes(std::vector< Polygon > & data, std::istream & in, std::ostream & out);
}

#endif
