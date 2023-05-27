#include "point.h"
namespace
{
  std::istream &checkSentry(std::istream &in)
  {
    std::istream::sentry sentry(in);
    return in;
  }
}
std::istream &romanovich::operator>>(std::istream &in, romanovich::Point &dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  char openParenthesis = '(';
  char comma = ';';
  char closeParenthesis = ')';
  return in >> openParenthesis >> dest.x_ >> comma >> dest.y_ >> closeParenthesis;
}
bool romanovich::operator==(const romanovich::Point &lhs, const romanovich::Point &rhs)
{
  return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
}
bool romanovich::operator!=(const romanovich::Point &lhs, const romanovich::Point &rhs)
{
  return !(lhs == rhs);
}
romanovich::Point romanovich::operator-(const romanovich::Point &lhs, const romanovich::Point &rhs)
{
  return romanovich::Point{lhs.x_ - rhs.x_, lhs.y_ - rhs.y_};
}
double romanovich::doScalarMultiplication(const romanovich::Point &v1, const romanovich::Point &v2)
{
  return v1.x_ * v2.x_ + v1.y_ * v2.y_;
}
romanovich::Point &romanovich::Point::operator=(const romanovich::Point &rhs)
{
  if (this != &rhs)
  {
    x_ = rhs.x_;
    y_ = rhs.y_;
  }
  return *this;
}
romanovich::Point::Point(const Point &rhs):
  x_(rhs.x_),
  y_(rhs.y_)
{
}
romanovich::Point::Point(int x, int y):
  x_(x),
  y_(y)
{
}
