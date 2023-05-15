#ifndef T3_HELPFUNCTIONS_HPP
#define T3_HELPFUNCTIONS_HPP
#include "Polygon.hpp"

namespace malaya
{
  double getArea(const malaya::Polygon & polygon);
  std::string inputCommand(std::istream & in);
  void doCommand(std::vector< malaya::Polygon > data, std::string & command, std::istream & in, std::ostream & out);
  struct areaCounter
  {
    double operator()(const Point & left, const Point & right);
  };
}

#endif
