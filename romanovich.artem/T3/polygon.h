#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <cstddef>
#include "point.h"
class Polygon
{
public:
  explicit Polygon(const std::vector< Point > &points);
  size_t pointsCount() const;
  const Point &getPoint(size_t index) const;
  double getArea() const;
private:
  std::vector< Point > points_;
};
#endif
