#include "polygon.h"
#include "iostructs.h.h"
std::istream & avdeeva::operator>>(std::istream & in, const Point & rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point input{0, 0};
  in >> DelimiterIO{'('} >> input.x >> DelimiterIO{';'} >> input.y >> DelimiterIO{')'};
  if (in)
  {
    rhs = input;
  }
  return in;
}
std::istream & avdeeva::operator>>(std::istream & in, const Polygon & rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Polygon input;
  size_t verts = 0;
  in >> verts;
  if (!in || verts < 3)
  {
    in.setstate(std::ios::failbit);
  }
  input.points.reserve(verts);
  using inIter = std::istream_iterator< Point >;
  std::copy_n(inIter(in), verts, std::back_inserter(input.points));
  if (in)
  {
    rhs.points.swap(input.points);
  }
  return in;
}
double avdeeva::areaCounter(const Point & lhs, const Point & rhs)
{
  return 0.5 * (lhs.x * rhs.y - rhs.x * lhs.y);
}