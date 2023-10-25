#ifndef COMMANDMAP_H
#define COMMANDMAP_H
#include <map>
#include <iostream>
#include <vector>
#include "polygon.h"

namespace aksenov
{
  using commandMap = std::map< std::string, void (*)(std::istream&, const std::vector< Polygon >&) >;
  commandMap makeDict();
}
#endif
