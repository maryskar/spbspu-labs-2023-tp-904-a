#include "polygon.hpp"
#include <algorithm>
#include <iterator>

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
  std::ostream& operator<<(std::ostream& out, const Point& rhs)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    return out << '(' << rhs.x << ';' << rhs.y << ')';
  }
  std::istream& operator>>(std::istream& in, Polygon& rhs)
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
    using in_point_iter = std::istream_iterator< Point >;
    std::copy_n(in_point_iter(in), points, std::back_inserter(input.points));
    if (in)
    {
      std::string temp = "";
      std::getline(in, temp);
      if (temp.empty())
      {
        rhs.points.swap(input.points);
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    return in;
  }
  std::ostream& operator<<(std::ostream& out, const Polygon& rhs)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    size_t points = rhs.points.size();
    out << points;
    std::copy_n(rhs.points.begin(), points - 1, std::ostream_iterator< Point >(out << ' ', " "));
    return out << rhs.points.back();
  }
  bool operator==(const Point& lhs, const Point& rhs)
  {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
  }
}
