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
  void countNumVertexes(size_t n, const std::vector< Polygon > &dest, std::ostream &out);
  void inFrame(const Polygon &pol, std::ostream &out);
  void isSame(const std::vector< Polygon > &dest, const Polygon &pol, std::ostream &out);
}
#endif
