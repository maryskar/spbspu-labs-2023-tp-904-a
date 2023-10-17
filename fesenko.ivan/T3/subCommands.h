#ifndef SUBCOMMANDS_H
#define SUBCOMMANDS_H
#include <iostream>
#include <deque>
#include "polygon.h"
namespace fesenko
{
  using data_t = std::deque< Polygon >;
  std::ostream &area_vertexes(const data_t &data, size_t number, std::ostream &out);
  std::ostream &count_vertexes(const data_t &data, size_t number, std::ostream &out);

  std::ostream &area_odd(const data_t &data, std::ostream &out);
  std::ostream &area_even(const data_t &data, std::ostream &out);
  std::ostream &area_mean(const data_t &data, std::ostream &out);
  std::ostream &max_area(const data_t &data, std::ostream &out);
  std::ostream &max_vertexes(const data_t &data, std::ostream &out);
  std::ostream &min_area(const data_t &data, std::ostream &out);
  std::ostream &min_vertexes(const data_t &data, std::ostream &out);
  std::ostream &count_odd(const data_t &data, std::ostream &out);
  std::ostream &count_even(const data_t &data, std::ostream &out);
  std::ostream &rects(const data_t &data, std::ostream &out);

  std::ostream &inframe(const data_t &data, std::istream &in, std::ostream &out);
}
#endif
