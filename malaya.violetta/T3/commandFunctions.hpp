#ifndef T3_COMMANDFUNCTIONS_HPP
#define T3_COMMANDFUNCTIONS_HPP
#include "Polygon.hpp"
namespace malaya
{
  void outAreaOdd(const std::vector< Polygon > & polygons, std::ostream & out);
  void outAreaEven(const std::vector< Polygon > & polygons, std::ostream & out);
  void outMinArea(const std::vector< Polygon > & data, std::ostream & out);
  void outMaxArea(const std::vector< Polygon > & data, std::ostream & out);
  void outAreaNum(const std::vector< Polygon > & polygons, size_t num, std::ostream & out);
  void outAreaMean(const std::vector< Polygon > & data, std::ostream & out);
  void outMinVertexes(const std::vector< Polygon > & data, std::ostream & out);
  void outMaxVertexes(const std::vector< Polygon > & data, std::ostream & out);
  void outCountEven(const std::vector< Polygon > & data, std::ostream & out);
  void outCountOdd(const std::vector< Polygon > & data, std::ostream & out);
  void outCountNum(const std::vector< Polygon > & data, size_t num, std::ostream & out);
  void outRects(const std::vector< Polygon > & data, std::ostream & out);
  void outPerms(const std::vector< Polygon > & data, std::ostream & out, std::istream & in);
}
#endif
