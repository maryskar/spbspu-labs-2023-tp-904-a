#ifndef SUB_COMMANDS_HPP
#define SUB_COMMANDS_HPP

#include <deque>
#include <string>

#include "data-structs.hpp"

namespace turkin
{
  using data_t = std::deque< Polygon >;
  ReturnType area_odd(data_t & data, std::string &);
  ReturnType area_even(data_t & data, std::string &);
  ReturnType area_mean(data_t & data, std::string &);
  ReturnType area_vertexes(data_t & data, std::string & in);
  ReturnType max_area(data_t & data, std::string &);
  ReturnType max_vertexes(data_t & data, std::string &);
  ReturnType min_area(data_t & data, std::string &);
  ReturnType min_vertexes(data_t & data, std::string &);
  ReturnType count_odd(data_t & data, std::string &);
  ReturnType count_even(data_t & data, std::string &);
  ReturnType count_vertexes(data_t & data, std::string & in);
  ReturnType maxseq_sub(data_t & data, std::string & in);
  ReturnType rightshapes_sub(data_t & data, std::string &);
}

#endif
