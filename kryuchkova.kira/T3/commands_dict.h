#ifndef COMMANDS_DICT_H
#define COMMANDS_DICT_H
#include <map>
#include <vector>
#include <ostream>
#include <istream>
#include "polygon.h"
#include "dict_functions.h"

namespace kryuchkova
{
  class CommandDict
  {
    using comm_t = void(*)(const std::vector< Polygon > & pol, std::ostream & out);
    using comm_input_t = void(*)(const std::vector< Polygon > & pol, std::ostream & out, std::istream & in);
    using comm_size_t = void(*)(const std::vector< Polygon > & pol, std::ostream & out, size_t n);
  public:
    CommandDict();
    void handleCommand(std::string comm, const std::vector< Polygon > & pol, std::ostream & out, std::istream & in);
  private:
    std::map< std::string, comm_t > simple_comm_;
    std::map< std::string, comm_input_t > input_comm_;
    std::map< std::string, comm_size_t > size_comm_;
  };
}

#endif
