#ifndef READPOLYGONS_H
#define READPOLYGONS_H

#include <deque>
#include <istream>
#include "dataStruct.h"

namespace potapova
{
  std::deque< Polygon > readPolygons(std::istream& in);
}

#endif
