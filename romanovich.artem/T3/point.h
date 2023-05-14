#ifndef POINT_H
#define POINT_H
#include <istream>
struct Point
{
  int x;
  int y;
};
std::istream &operator>>(std::istream &in, Point &dest);
bool operator==(const Point &lhs, const Point &rhs);
bool operator!=(const Point &lhs, const Point &rhs);
Point operator-(const Point &lhs, const Point &rhs);
double doScalarMultiplication(const Point &v1, const Point &v2);
#endif
