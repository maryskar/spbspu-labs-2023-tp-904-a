#include "polygon.h"
namespace aksenov
{
  bool operator==(const Point& lhs, const Point& rhs)
  {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
  }

  std::istream & operator>>(std::istream & in, Point & rhs)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Point input{0, 0};
    using del = DelimiterIO;
    in >> del{'('} >> input.x >> del{';'} >> input.y >> del{')'};
    if (in)
    {
      rhs = input;
    }
    return in;
  }

  std::istream & operator>>(std::istream & in, Polygon & rhs)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Polygon input;
    size_t points = 0;
    in >> points;
    if (points < 3)
    {
      in.setstate(std::ios::failbit);
    }
    input.points.reserve(points);
    std::copy_n(std::istream_iterator< Point >(in), points, std::back_inserter(input.points));
    if (in)
    {
      rhs.points.swap(input.points);
    }
    return in;
  }
}
