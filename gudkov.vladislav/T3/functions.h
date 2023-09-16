#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Polygon.h"

namespace gudkov
{
  double getSide(const Point &a, const Point &b);
  double getTriangleArea(const Point &a, const Point &b, const Point &c);
  double getArea(const Polygon &polygon);
  bool isEvenVertexesCount(const Polygon &polygon);
  bool isOddVertexesCount(const Polygon &polygon);
  bool isEqualVertexesCount(const Polygon &polygon, size_t count);
  bool isLessByArea(const Polygon &a, const Polygon &b);
  bool isLessByVertexes(const Polygon &a, const Polygon &b);
  bool isLessPoints(const Point &a, const Point &b);
  bool isEqualCoordinates(const Point &a, const Point &b);
  bool isEqualPolygons(const Polygon &a, const Polygon &b);

  double areaEven(const std::vector< Polygon > &data);
  double areaOdd(const std::vector< Polygon > &data);
  double areaMean(const std::vector< Polygon > &data);
  double areaVertexes(const std::vector< Polygon > &data, size_t count);

  double maxArea(const std::vector< Polygon > &data);
  size_t maxVertexes(const std::vector< Polygon > &data);

  double minArea(const std::vector< Polygon > &data);
  size_t minVertexes(const std::vector< Polygon > &data);

  size_t countEven(const std::vector< Polygon > &data);
  size_t countOdd(const std::vector< Polygon > &data);
  size_t countVertexes(const std::vector< Polygon > &data, size_t count);

  size_t permutations(const std::vector< Polygon > &data, const Polygon &polygon);
  size_t lessArea(const std::vector< Polygon > &data, const Polygon &polygon);
}
#endif
