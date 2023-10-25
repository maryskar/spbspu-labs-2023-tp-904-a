#ifndef READPOLYGONS_H
#define READPOLYGONS_H

#include <deque>
#include <istream>
#include "dataStructs.h"

namespace potapova
{
  std::deque< Polygon > readPolygons(std::istream& in);
}

#endif
