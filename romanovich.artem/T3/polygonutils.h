#ifndef POLYGONUTILS_H
#define POLYGONUTILS_H
#include "polygon.h"
#include <istream>
namespace romanovich
{
  size_t getPointsCount(const Polygon &p);
  double getArea(const Polygon &p);
  bool operator==(const Polygon &lhs, const Polygon &rhs);
  std::istream &operator>>(std::istream &in, Polygon &dest);
  typename std::vector< Point >::const_iterator begin();
  typename std::vector< Point >::const_iterator end();
  typename std::vector< Point >::const_iterator begin(const Polygon &p);
  typename std::vector< Point >::const_iterator end(const Polygon &p);
}
#endif
