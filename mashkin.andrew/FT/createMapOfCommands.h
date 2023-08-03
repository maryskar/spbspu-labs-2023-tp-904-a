#ifndef MASHKIN_ANDREW_CREATEMAPOFCOMMANDS_H
#define MASHKIN_ANDREW_CREATEMAPOFCOMMANDS_H
#include <map>
#include <iostream>
#include <string>
#include "semanticTree.h"

namespace mashkin
{
  using MapOfExpressions = std::map< std::string, SemanticTree< std::string >* >;
  using MapOfCommands = std::map< std::string, void (*)(std::istream&, MapOfExpressions&) >;
  void createMapOfCommands(MapOfCommands& mapOfCommands);
}
#endif
