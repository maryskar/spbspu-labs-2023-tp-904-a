#include "polygon.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <delimiter.h>
#include <streamsguard.h>

namespace chulkov {
  std::istream& operator>>(std::istream& in, Point& point)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    in >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'} >> point.y >> DelimiterIO{')'};
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    dest.points.clear();
    size_t inpNum = 0;
    in >> inpNum;
    if (inpNum < 3) {
      in.setstate(std::ios::failbit);
    }
    std::copy_n(std::istream_iterator< Point >(in), inpNum, std::back_inserter(dest.points));
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Point& point)
  {
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }
    StreamGuard quard(out);
    out << std::fixed << std::setprecision(1);
    return out << '(' << point.x << ';' << point.y << ')';
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }
    using ostreamIter = std::ostream_iterator< Point >;
    std::copy(dest.points.cbegin(), dest.points.cend(), ostreamIter(out));
    return out;
  }

  bool operator==(const Point& frs, const Point& sec)
  {
    return (frs.x == sec.x) && (frs.y == sec.y);
  }

  bool operator!=(const Point& frs, const Point& sec)
  {
    return !(frs == sec);
  }

  bool operator==(const Polygon& frs, const Polygon& sec)
  {
    return frs.points.size() == sec.points.size() && std::equal(frs.points.begin(), frs.points.end(), sec.points.begin());
  }
}
