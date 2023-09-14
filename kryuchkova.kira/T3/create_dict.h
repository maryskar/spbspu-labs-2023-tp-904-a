#ifndef CREATE_DICT_H
#define CREATE_DICT_H
#include <map>
#include <ostream>
#include <istream>
#include "polygon.h"

namespace kryuchkova
{
  using comm_t = void(*)(const std::vector< Polygon > & pol, std::ostream & out);
  using comm_input_t = void(*)(const std::vector< Polygon > & pol, std::ostream & out, std::istream & in);
  using comm_size_t = void(*)(const std::vector< Polygon > & pol, std::ostream & out, size_t n);

  struct command_dict
  {
    std::map< std::string, comm_t > dict_first;
    std::map< std::string, comm_size_t > dict_second;
    std::map< std::string, comm_input_t > dict_third;
  };
  command_dict createCommandDict();
}

#endif
