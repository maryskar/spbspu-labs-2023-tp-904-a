#ifndef READPOLYGONS_H
#define READPOLYGONS_H

#include <deque>
#include <iostream>
#include "data_struct.h"

namespace tarasenko
{
  std::deque< Polygon > readPolygons(std::istream& in);
}
#endif
