#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <iterator>
#include <algorithm>

namespace aksenov
{
  struct DelimiterIO
  {
    char exp;
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
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  struct Point
  {
    int x, y;
  };

  bool operator==(const Point& lhs, const Point& rhs)
  {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
  }

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream &operator>>(std::istream &input, Point &point)
  {
    input >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'};
    input >> point.y >> DelimiterIO{')'};
    return input;
  }

  std::istream &operator>>(std::istream &input, Polygon &polygon)
  {
    using inputIter = std::istream_iterator< Point >;
    size_t pointNum = 0;
    input >> pointNum;
    std::copy_n(inputIter(input),pointNum, std::back_inserter(polygon.points));
    return input;
  }
}
#endif
