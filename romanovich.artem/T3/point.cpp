#include "pointutils.h"
namespace
{
  struct DelimiterIO
  {
    char symbol;
  };
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.symbol))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
std::istream &romanovich::operator>>(std::istream &in, Point &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{'('} >> dest.x >> DelimiterIO{';'};
  in >> dest.y >> DelimiterIO{')'};
  return in;
}
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
