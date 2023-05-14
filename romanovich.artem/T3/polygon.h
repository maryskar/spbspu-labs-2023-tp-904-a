#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <cstddef>
#include "point.h"
class Polygon
{
public:
  Polygon(const std::vector< Point > &points);
  size_t pointsCount() const;
  const Point &getPoint(size_t index) const;
private:
  std::vector< Point > points_;
};
#endif
