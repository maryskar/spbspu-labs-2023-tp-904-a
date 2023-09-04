#ifndef SUB_COMMANDS_HPP
#define SUB_COMMANDS_HPP

#include <deque>
#include <istream>
#include <ostream>

#include "data-structs.hpp"

namespace turkin
{
  using data_t = std::deque< Polygon >;
  ReturnType area_odd(data_t & data, std::istream &);
  ReturnType area_even(data_t & data, std::istream &);
  ReturnType area_mean(data_t & data, std::istream &);
  ReturnType area_vertexes(data_t & data, std::istream & in);
  ReturnType max_area(data_t & data, std::istream &);
  ReturnType max_vertexes(data_t & data, std::istream &);
  ReturnType min_area(data_t & data, std::istream &);
  ReturnType min_vertexes(data_t & data, std::istream &);
  ReturnType count_odd(data_t & data, std::istream &);
  ReturnType count_even(data_t & data, std::istream &);
  ReturnType count_vertexes(data_t & data, std::istream & in);
  ReturnType maxseq_sub(data_t & data, std::istream & in);
  ReturnType rightshapes_sub(data_t & data, std::istream &);
}

#endif
