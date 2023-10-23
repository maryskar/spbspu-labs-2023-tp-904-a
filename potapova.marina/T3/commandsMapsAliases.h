#ifndef COMMANDSMAPSALIASES_H
#define COMMANDSMAPSALIASES_H

#include <unordered_map>
#include <functional>
#include <deque>
#include <iostream>
#include "dataStructs.h"

namespace potapova
{
  template < typename Polygons >
  using CommandFunc = std::function< void(Polygons&, std::istream&, std::ostream&, std::ostream&) >;
  template < typename CommandFunc >
  using CommandsMap = std::unordered_map< std::string, CommandFunc >;
  using ChangingCommansMap = CommandsMap< CommandFunc< std::deque< Polygon > > >;
  using NotChangingCommansMap = CommandsMap< CommandFunc< const std::deque< Polygon > > >;
  using PoligonsConstIterator = std::deque< Polygon >::const_iterator;
  using ComparePolygonsFunc = bool(*)(const Polygon&, const Polygon&);
  using GetExtremeElemFunc = PoligonsConstIterator(*)(PoligonsConstIterator, PoligonsConstIterator, ComparePolygonsFunc);
}

#endif
