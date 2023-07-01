#ifndef READPOLYGONS_H
#define READPOLYGONS_H

#include <vector>
#include <iostream>
#include "data_struct.h"

namespace tarasenko
{
  std::vector< Polygon > readPolygons(std::ifstream& in);
}
#endif
