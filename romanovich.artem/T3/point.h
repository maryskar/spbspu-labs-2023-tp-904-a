#ifndef POINT_H
#define POINT_H
#include <istream>
namespace romanovich
{
  struct Point
  {
    int x;
    int y;
    Point &operator=(const Point &rhs);
  };
  bool operator==(const Point &lhs, const Point &rhs);
  bool operator!=(const Point &lhs, const Point &rhs);
  Point operator-(const Point &lhs, const Point &rhs);
  std::istream &operator>>(std::istream &in, Point &dest);
  double doScalarMultiplication(const Point &v1, const Point &v2);
}
#endif
