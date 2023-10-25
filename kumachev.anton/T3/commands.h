#ifndef T3_COMMANDS_H
#define T3_COMMANDS_H

#include <iosfwd>
#include "polygon.h"

namespace kumachev {
  void areaEven(const std::vector< Polygon > &polygons, std::ostream &ostream);
  void areaOdd(const std::vector< Polygon > &polygons, std::ostream &ostream);
  void areaMean(const std::vector< Polygon > &polygons, std::ostream &ostream);

  void areaVertex(const std::vector< Polygon > &polygons, size_t vertex,
      std::ostream &ostream);

  void maxArea(const std::vector< Polygon > &polygons, std::ostream &ostream);
  void maxVert(const std::vector< Polygon > &polygons, std::ostream &ostream);
  void minArea(const std::vector< Polygon > &polygons, std::ostream &ostream);
  void minVert(const std::vector< Polygon > &polygons, std::ostream &ostream);
  void countEven(const std::vector< Polygon > &polygons, std::ostream &ostream);
  void countOdd(const std::vector< Polygon > &polygons, std::ostream &ostream);
  void countVert(const std::vector< Polygon > &polygons, size_t vertex,
      std::ostream &ostream);

  void echo(std::vector< Polygon > &polygons, const Polygon &polygon,
      std::ostream &ostream);

  void rmEcho(std::vector< Polygon > &polygons, const Polygon &polygon,
      std::ostream &ostream);
}

#endif
