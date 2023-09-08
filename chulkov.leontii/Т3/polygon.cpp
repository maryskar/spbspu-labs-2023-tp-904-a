#include "polygon.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <streamsguard.h>
#include <iostruct.h>

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

}
