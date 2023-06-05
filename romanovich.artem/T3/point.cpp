#include "point.h"
std::istream &romanovich::operator>>(std::istream &in, romanovich::Point &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char openParenthesis = '(';
  char comma = ';';
  char closeParenthesis = ')';
  return in >> openParenthesis >> dest.x >> comma >> dest.y >> closeParenthesis;
}
bool romanovich::operator==(const romanovich::Point &lhs, const romanovich::Point &rhs)
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
romanovich::Point &romanovich::Point::operator=(const romanovich::Point &rhs)
{
  x = rhs.x;
  y = rhs.y;
  return *this;
}
