#ifndef SUBCOMMANDS_H
#define SUBCOMMANDS_H
#include <iostream>
#include <deque>
#include "polygon.h"
#include "returnType.h"
namespace fesenko
{
  using data_t = std::deque< Polygon >;
  ReturnType area_odd(data_t &data);
  ReturnType area_even(data_t &data);
  ReturnType area_mean(data_t &data);
  ReturnType area_vertexes(data_t &data, std::istream &in);
  ReturnType max_area(data_t &data);
  ReturnType max_vertexes(data_t &data);
  ReturnType min_area(data_t &data);
  ReturnType min_vertexes(data_t &data);
  ReturnType count_odd(data_t &data);
  ReturnType count_even(data_t &data);
  ReturnType count_vertexes(data_t &data, std::istream &in);
  ReturnType rects_sub(data_t &data, std::istream &in);
  ReturnType inframe_sub(data_t &data, std::istream &in);
}
#endif
