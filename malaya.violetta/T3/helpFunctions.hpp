#ifndef T3_HELPFUNCTIONS_HPP
#define T3_HELPFUNCTIONS_HPP
#include "Polygon.hpp"

namespace malaya
{
  std::string inputCommand(std::istream & in);
  void doCommand(const std::vector< malaya::Polygon > & data, std::string & command, std::istream & in, std::ostream & out);
  void invalidPrint(std::ostream & out);
}
#endif
