#include "point.h"
#include "io.h"
std::istream &dimkashelk::operator>>(std::istream &in, dimkashelk::Point &point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{'('};
  in >> point.x;
  in >> DelimiterIO{';'};
  in >> point.y;
  in >> DelimiterIO{')'};
  return in;
}
bool dimkashelk::operator==(const dimkashelk::Point &p1, const dimkashelk::Point &p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}
