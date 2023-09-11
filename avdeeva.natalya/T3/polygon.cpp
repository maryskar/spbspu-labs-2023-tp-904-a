#include "polygon.h"
#include "iostructs.h.h"
std::istream & avdeeva::operator>>(std::istream & in, const Point & rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point input {0, 0};
  in >> DelimiterIO{'('} >> input.x >> DelimiterIO{';'} >> input.y >> DelimiterIO{')'};
  if (in)
  {
    rhs = input;
  }
  return in;
}