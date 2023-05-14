#ifndef T3_CREATE_COMMAND_DICTIONARY_HPP
#define T3_CREATE_COMMAND_DICTIONARY_HPP
#include <map>
#include <vector>
#include "polygon.hpp"

namespace chemodurov
{
  using area_comm_t = void(*)(const std::vector< Polygon > & data, std::ostream & out);
  std::map< std::string, area_comm_t > createCommandDictionary();
}

#endif
