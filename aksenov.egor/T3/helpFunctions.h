#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H
#include <vector>
#include <string>
#include "polygon.h"

namespace aksenov
{
  std::vector< double > getArea(const std::vector<Polygon> &pol);
  bool isOdd(const Polygon& data);
  bool isEven(const Polygon& data);
  bool isInteger(const std::string & s);
}
#endif
