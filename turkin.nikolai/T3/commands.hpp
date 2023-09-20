#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <deque>
#include <istream>
#include <ostream>

#include "data-structs.hpp"
#include "sub-commands-list.hpp"

namespace turkin
{
  using data_t = std::deque< Polygon >;
  ReturnType area(data_t & data, SubCommandsList & list, std::string & type, std::string & sub_info);
  ReturnType min(data_t & data, SubCommandsList & list, std::string & type, std::string & sub_info);
  ReturnType max(data_t & data, SubCommandsList & list, std::string & type, std::string & sub_info);
  ReturnType count(data_t & data, SubCommandsList & list, std::string & type, std::string & sub_info);
  ReturnType maxseq(data_t & data, SubCommandsList & list, std::string & type, std::string & sub_info);
  ReturnType rightshapes(data_t & data, SubCommandsList & list, std::string & type, std::string &);
}

#endif
