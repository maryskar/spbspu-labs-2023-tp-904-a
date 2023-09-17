#ifndef COMMANDS_H
#define COMMANDS_H
#include "datastructs.h"

namespace azheganova
{
  void area(std::vector< Polygon > & polygon, std::istream & in, std::ostream & out);
  void max(std::vector< Polygon > & polygon, std::istream & in, std::ostream & out);
  void min(std::vector< Polygon > & polygon, std::istream & in, std::ostream & out);
  void count(std::vector< Polygon > & polygon, std::istream & in, std::ostream & out);
  void rmecho(std::vector< Polygon > & polygon, std::istream & in, std::ostream & out);
  void rightshapes(std::vector< Polygon > & polygon, std::ostream & out);
  std::ostream & printInvalidCommand(std::ostream & out);
}

#endif
