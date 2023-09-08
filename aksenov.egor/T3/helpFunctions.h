#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H
#include <vector>
#include "polygon.h"

namespace aksenov
{
  std::vector< double > getArea(const std::vector<Polygon> &pol);
}
#endif
