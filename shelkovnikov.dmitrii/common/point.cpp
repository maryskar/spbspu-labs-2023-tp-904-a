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
