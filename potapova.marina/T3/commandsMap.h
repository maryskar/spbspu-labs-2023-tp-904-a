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

  std::unordered_map< std::string, CommandFunc< const std::deque< Polygon > > > getNonChangingCommands();
  std::unordered_map< std::string, CommandFunc< std::deque< Polygon > > > getChangingCommands();
}

#endif
