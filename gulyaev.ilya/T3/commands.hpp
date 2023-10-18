#ifndef T3_COMMANDS_HPP
#define T3_COMMANDS_HPP
#include <string>
#include "polygon.hpp"

namespace gulyaev
{
  void printArea(const std::vector< Polygon > &data, std::istream &in, std::ostream &out);
  void printMax(const std::vector< Polygon > &data, std::istream &in, std::ostream &out);
  void printMin(const std::vector< Polygon > &data, std::istream &in, std::ostream &out);
  void printCount(const std::vector< Polygon > &data, std::istream &in, std::ostream &out);
  void printPerms(const std::vector< Polygon > &data, std::istream &in, std::ostream &out);
  void printRightShapes(const std::vector< Polygon > &data, std::istream &in, std::ostream &out);
}
#endif
