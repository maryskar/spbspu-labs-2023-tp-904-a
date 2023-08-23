#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <vector>
#include "point-struct.hpp"

namespace turkin
{
  double area(std::vector< Polygon > & data, std::istream & in);
  double min(std::vector< Polygon > & data, std::istream & in);
  double max(std::vector< Polygon > & data, std::istream & in);
  double count(std::vector< Polygon > & data, std::istream & in);
  double maxseq(std::vector< Polygon > & data, std::istream & in);
  double rightshapes(std::vector< Polygon > & data, std::istream & in);
}

#endif
