#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <algorithm>
#include "pointutils.h"
namespace romanovich
{
  class Polygon
  {
  public:
    explicit Polygon(const std::vector< Point > &points);
    size_t getPointsCount() const;
    Point getPoint(size_t index) const;
    double getArea() const;
    bool operator==(const Polygon &rhs) const;
    typename std::vector< Point >::const_iterator begin() const;
    typename std::vector< Point >::const_iterator end() const;
  private:
    std::vector< Point > points_;
  };
}
#endif
