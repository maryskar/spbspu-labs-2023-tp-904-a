#include "point.h"
#include <iostream>
std::istream &checkSentry(std::istream &in)
{
  std::istream::sentry sentry(in);
  return in;
}
std::istream &operator>>(std::istream &in, Point &dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  char openParenthesis = '(';
  char comma = ';';
  char closeParenthesis = ')';
  return in >> openParenthesis >> dest.x >> comma >> dest.y >> closeParenthesis;
}
bool operator==(const Point &lhs, const Point &rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool operator!=(const Point &lhs, const Point &rhs)
{
  return !(lhs == rhs);
}
Point operator-(const Point &lhs, const Point &rhs)
{
  return Point{lhs.x - rhs.x, lhs.y - rhs.y};
}
double doScalarMultiplication(const Point &v1, const Point &v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}
