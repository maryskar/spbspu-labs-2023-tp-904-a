#ifndef COMMANDS_H
#define COMMADNS_H
#include <iostream>
#include "polygon.h"
namespace fesenko
{
  using data_t = std::vector< Polygon >;
  std::ostream &area(data_t &data, std::istream &in, std::ostream &out);
  std::ostream &max(data_t &data, std::istream &in, std::ostream &out);
  std::ostream &min(data_t &data, std::istream &in, std::ostream &out);
  std::ostream &count(data_t &data, std::istream &in, std::ostream &out);
  std::ostream &rects(data_t &data, std::istream &in, std::ostream &out);
  std::ostream &inframe(data_t &data, std::istream &in, std::ostream &out);
}
#endif
