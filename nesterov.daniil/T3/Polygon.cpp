#include "Polygon.h"
#include <iterator>
#include <algorithm>
#include <IOStructs.h>

namespace nesterov
{
  std::istream &operator>>(std::istream &in, nesterov::Point &rhs)
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

  std::ostream &operator<<(std::ostream &out, const nesterov::Point &rhs)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    return out << '(' << rhs.x << ';' << rhs.y << ')';
  }

  std::istream &operator>>(std::istream &in, nesterov::Polygon &rhs)
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
    std::copy_n(
      std::istream_iterator< Point >(in),
      points,
      std::back_inserter(input.points)
    );

    if (in)
    {
      rhs.points.swap(input.points);
    }
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const nesterov::Polygon &rhs)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    size_t points = rhs.points.size();
    out << points;
    std::copy_n(
      rhs.points.begin(),
      points - 1,
      std::ostream_iterator< Point >(out << ' ', " ")
    );
    return out << rhs.points.back();
  }

  bool operator==(const Polygon &lhs, const Polygon &rhs)
  {
    return lhs.points == rhs.points;
  }

  bool operator==(const Point &lhs, const Point &rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  bool operator!=(const Polygon &lhs, const Polygon &rhs)
  {
    return !(lhs == rhs);
  }
}
