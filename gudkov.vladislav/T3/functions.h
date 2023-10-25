#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "polygon.h"

namespace gudkov
{
  bool isEvenVertexesCount(const Polygon &polygon);
  bool isOddVertexesCount(const Polygon &polygon);
  bool isEqualVertexesCount(const Polygon &polygon, size_t count);
  bool isLessByArea(const Polygon &a, const Polygon &b);
  bool isLessByVertexes(const Polygon &a, const Polygon &b);
  bool isLessPoints(const Point &a, const Point &b);
  bool isEqualCoordinates(const Point &a, const Point &b);
  bool isEqualPolygons(const Polygon &a, const Polygon &b);

  double calcAreaEven(const std::vector< Polygon > &data);
  double calcAreaOdd(const std::vector< Polygon > &data);
  double calcAreaMean(const std::vector< Polygon > &data);
  double calcAreaVertexes(const std::vector< Polygon > &data, size_t count);

  double getMaxArea(const std::vector< Polygon > &data);
  size_t getMaxVertexes(const std::vector< Polygon > &data);

  double getMinArea(const std::vector< Polygon > &data);
  size_t getMinVertexes(const std::vector< Polygon > &data);

  size_t getCountEven(const std::vector< Polygon > &data);
  size_t getCountOdd(const std::vector< Polygon > &data);
  size_t getCountVertexes(const std::vector< Polygon > &data, size_t count);

  size_t getPermutationsCount(const std::vector< Polygon > &data, const Polygon &polygon);
  size_t getLessAreaCount(const std::vector< Polygon > &data, const Polygon &polygon);
}
#endif
