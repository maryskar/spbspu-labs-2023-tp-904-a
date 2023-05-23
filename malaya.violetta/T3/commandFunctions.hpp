#ifndef T3_COMMANDFUNCTIONS_HPP
#define T3_COMMANDFUNCTIONS_HPP
#include "Polygon.hpp"

namespace malaya
{
  void outAreaOdd(const std::vector< malaya::Polygon > & polygons, std::ostream & out);
  void outAreaEven(const std::vector< malaya::Polygon > & polygons, std::ostream & out);
  void outMinArea(const std::vector< malaya::Polygon > & data, std::ostream & out);
  void outMaxArea(const std::vector< malaya::Polygon > & data, std::ostream & out);
  void outAreaNum(const std::vector< malaya::Polygon > & polygons, size_t num, std::ostream & out);
  void outMeanArea(const std::vector< malaya::Polygon > & data, std::ostream & out);
  void outMinVertexes(const std::vector< malaya::Polygon > & data, std::ostream & out);
  void outMaxVertexes(const std::vector< malaya::Polygon > & data, std::ostream & out);
  void outCountEven(const std::vector< malaya::Polygon > & data, std::ostream & out);
  void outCountOdd(const std::vector< malaya::Polygon > & data, std::ostream & out);
  void outCountNum(const std::vector< malaya::Polygon > & data, size_t num, std::ostream & out);
  void rects(const std::vector< malaya::Polygon > & data, std::ostream & out);

}

#endif
