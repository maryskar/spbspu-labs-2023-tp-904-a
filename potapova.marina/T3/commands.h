#ifndef COMMANDS_H
#define COMMANDS_H

#include <deque>
#include "dataStruct.h"

namespace potapova
{
  double calculatePolygonArea(const Polygon& polygon);
  double calculateAverageArea(const std::deque< Polygon >& polygons);
}

#endif
