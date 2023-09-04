#include "pointutils.h"
bool romanovich::operator==(const Point &lhs, const Point &rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool romanovich::operator!=(const romanovich::Point &lhs, const romanovich::Point &rhs)
{
  return !(lhs == rhs);
}
romanovich::Point romanovich::operator-(const romanovich::Point &lhs, const romanovich::Point &rhs)
{
  return romanovich::Point{lhs.x - rhs.x, lhs.y - rhs.y};
}
double romanovich::doScalarMultiplication(const romanovich::Point &v1, const romanovich::Point &v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}
