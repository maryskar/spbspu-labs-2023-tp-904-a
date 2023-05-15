#ifndef T3_CREATE_COMMAND_DICTIONARY_HPP
#define T3_CREATE_COMMAND_DICTIONARY_HPP
#include <map>
#include <vector>
#include "polygon.hpp"

namespace chemodurov
{
  using comm_t = void(*)(const std::vector< Polygon > & data, std::ostream & out);
  using comm_with_size_t = void(*)(const std::vector< Polygon > & data, std::ostream & out, size_t n);
  using comm_with_input_t = void(*)(const std::vector< Polygon > & data, std::ostream & out, std::istream & in);
  struct comm_dics_t
  {
    std::map< std::string, comm_t > dic1;
    std::map< std::string, comm_with_size_t > dic2;
    std::map< std::string, comm_with_input_t > dic3;
  };
  comm_dics_t createCommandDictionary();
}

#endif
