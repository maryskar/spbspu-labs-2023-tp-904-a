#ifndef T3_CREATE_COMMAND_DICTIONARY_HPP
#define T3_CREATE_COMMAND_DICTIONARY_HPP
#include <map>
#include <vector>
#include "polygon.hpp"

namespace chemodurov
{
  using comm_t = void(*)(const std::vector< Polygon > & data, std::ostream & out);
  using comm_with_size_t = void(*)(const std::vector< Polygon > & data, std::ostream & out, size_t n);
  std::map< std::string, comm_t > createCommandDictionary();
}

#endif
