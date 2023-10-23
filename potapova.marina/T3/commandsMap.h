#ifndef COMMANDSMAP_H
#define COMMANDSMAP_H

#include <unordered_map>
#include <functional>
#include <deque>
#include <string>
#include "dataStructs.h"

namespace potapova
{
  template < typename Polygons >
  using CommandFunc = std::function< void(Polygons&, std::istream&, std::ostream&, std::ostream&) >;
  template < typename CommandFunc >
  using CommandsMap = std::unordered_map< std::string, CommandFunc >;
  using ChangingCommansMap = CommandsMap< CommandFunc< std::deque< Polygon > > >;
  using NotChangingCommansMap = CommandsMap< CommandFunc< const std::deque< Polygon > > >;

  NotChangingCommansMap getNonChangingCommands();
  ChangingCommansMap getChangingCommands();
}

#endif
