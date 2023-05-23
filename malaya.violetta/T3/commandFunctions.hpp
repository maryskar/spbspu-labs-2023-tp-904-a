#ifndef T3_COMMANDFUNCTIONS_HPP
#define T3_COMMANDFUNCTIONS_HPP
#include "Polygon.hpp"

namespace malaya
{
  void outAreaOdd(const std::vector< malaya::Polygon > & polygons, std::ostream & out);
  void outAreaEven(const std::vector< malaya::Polygon > & polygons, std::ostream & out);

  double areaNum(const Polygon & polygon, size_t num);
  double maxArea(std::vector< malaya::Polygon > data);

}

#endif
