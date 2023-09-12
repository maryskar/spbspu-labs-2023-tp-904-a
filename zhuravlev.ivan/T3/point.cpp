#include "point.hpp"

namespace zhuravlev
{
  std::istream& operator>>(std::istream& in, Point& rhs)
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
  std::istream& operator>>(std::istream& in, Polygon rhs)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Polygon input;
    size_t points;
    in >> points;
    input.points.reserve(points);
    using in_point_iter = std::istream_iterator< Point >;
    std::copy_n(in_point_iter(in), points, std::back_inserter(input));
    if (!in)
    {
      return in;
    }
    rhs.points.swap(input.points);
    return in;
  }
}
