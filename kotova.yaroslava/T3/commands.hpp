#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "geomfigures.hpp"
namespace kotova
{
  void areaEven(const std::vector< Polygon > &dest, std::ostream &out);
  void areaOdd(const std::vector< Polygon > &dest, std::ostream &out);
  void areaMean(const std::vector< Polygon > &dest, std::ostream &out);
  void areaNumVertexes(size_t n, const std::vector< Polygon > &dest, std::ostream &out);
  void maxArea(const std::vector< Polygon > &dest, std::ostream &out);
  void maxVertexes(const std::vector< Polygon > &dest, std::ostream &out);
  void minArea(const std::vector< Polygon > &dest, std::ostream &out);
  void minVertexes(const std::vector< Polygon > &dest, std::ostream &out);
  void countEven(const std::vector< Polygon > &dest, std::ostream &out);
  void countOdd(const std::vector< Polygon > &dest, std::ostream &out);
  void countNumVertexes(const std::vector< Polygon > &dest, std::ostream &out);
  void inframe(const std::vector< Polygon > &dest, std::ostream &out);
  void same(const std::vector< Polygon > &dest, std::ostream &out);
}
#endif
