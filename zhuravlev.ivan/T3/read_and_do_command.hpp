#ifndef READ_AND_DO_COMMAND_HPP
#define READ_AND_DO_COMMAND_HPP
#include <iostream>
#include "polygon.hpp"

namespace zhuravlev
{
  void readAndDoCommand(const std::vector< zhuravlev::Polygon >& polygons, std::istream& in, std::ostream& out);
}
#endif
