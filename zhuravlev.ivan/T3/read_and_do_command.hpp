#ifndef READ_AND_DO_COMMAND_HPP
#define READ_AND_DO_COMMAND_HPP
#include "polygon.hpp"

namespace zhuravlev
{
  std::string readCommand(std::istream& in);
  void doCommand(std::vector< Polygon >, std::istream& in, std::ostream& out, std::string command);
  void doConstCommand(std::vector< Polygon >& pls, std::istream& in, std::ostream& out, std::string cmd);
  void doCommandWithInput(std::vector< Polygon >& pls, std::ostream& out, const size_t condition, std::string command);
  void doCommandWithInputPolygon(std::vector< Polygon >& pls, std::istream& in, std::ostream& out, std::string cmd);
}
#endif
