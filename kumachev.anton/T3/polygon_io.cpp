#include "polygon_io.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include "basic_io.h"
#include "stream_guard.h"

namespace kumachev {

  std::istream &operator>>(std::istream &istream, Point &point)
  {
    std::istream::sentry sentry(istream);
    StreamGuard guard(istream);

    if (!sentry) {
      return istream;
    }

    Point value{ 0, 0 };
    istream >> CharIO{ '(' } >> value.x >> CharIO{ ';' };
    istream >> value.y >> CharIO{ ')' };

    if (istream) {
      point = value;
    }

    return istream;
  }

  std::istream &operator>>(std::istream &istream, Polygon &polygon)
  {
    using istream_iterator = std::istream_iterator< Point >;
    std::istream::sentry sentry(istream);
    StreamGuard guard(istream);

    if (!sentry) {
      return istream;
    }

    size_t vertexCount = 0;
    istream >> vertexCount;

    if (!istream || vertexCount < 3) {
      istream.setstate(std::ios::failbit);
      return istream;
    }

    Polygon value;
    value.points.reserve(vertexCount);
    auto backInserter = std::back_inserter(value.points);
    std::copy_n(istream_iterator(istream), vertexCount, backInserter);

    if (istream) {
      std::swap(polygon, value);
    }

    return istream;
  }
}
