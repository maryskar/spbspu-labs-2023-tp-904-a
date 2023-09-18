#include "polygon.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <inputStructs.h>

namespace mashkin
{
  std::istream& operator>>(std::istream& inp, Point& point)
  {
    std::istream::sentry sentry(inp);
    if (!sentry)
    {
      return inp;
    }
    inp >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'};
    inp >> point.y >> DelimiterIO{')'};
    return inp;
  }

  std::istream& operator>>(std::istream& inp, Polygon& dest)
  {
    std::istream::sentry sentry(inp);
    if (!sentry)
    {
      return inp;
    }
    Polygon input;
    size_t numOfPoints = 0;
    inp >> numOfPoints;
    if (numOfPoints < 3)
    {
      inp.setstate(std::ios::failbit);
      return inp;
    }
    using inpIter = std::istream_iterator< mashkin::Point >;
    input.points.reserve(numOfPoints);
    std::copy_n(inpIter(inp), numOfPoints, std::back_inserter(input.points));
    if (inp)
    {
      dest.points.swap(input.points);
    }
    return inp;
  }

  bool operator<(const Polygon& lhs, const Polygon& rhs)
  {
    return lhs.points.size() < rhs.points.size();
  }

  bool operator<(const Point& lhs, const Point& rhs)
  {
    if (lhs.x == rhs.x)
    {
      return lhs.y < rhs.y;
    }
    return lhs.x < rhs.x;
  }

  bool operator==(const Point& lhs, const Point& rhs)
  {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
  }
}
