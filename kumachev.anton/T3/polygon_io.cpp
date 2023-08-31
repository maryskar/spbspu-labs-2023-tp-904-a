#include "polygon_io.h"
#include "stream_guard.h"
#include <iostream>
#include <algorithm>
#include <iterator>

namespace kumachev {
  std::istream &operator>>(std::istream &istream, CharIO &&character)
  {
    std::istream::sentry sentry(istream);

    if (!sentry) {
      return istream;
    }

    char c = '\0';
    istream >> c;

    if (c != character.value) {
      istream.setstate(std::ios::failbit);
    }

    return istream;
  }

  std::istream &operator>>(std::istream &istream, Point &point)
  {
    std::istream::sentry sentry(istream);
    StreamGuard guard(istream);
    istream >> std::noskipws;

    if (!sentry) {
      return istream;
    }

    Point value{ 0, 0 };
    istream >> CharIO{ ' ' } >> CharIO{ '(' } >> value.x >> CharIO{ ';' } >> value.y;
    istream >> CharIO{ ')' };

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
    istream >> std::noskipws;

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
    auto backInserter = std::back_inserter(value.points);
    std::copy_n(istream_iterator(istream), vertexCount, backInserter);
    int nextChar = istream.peek();

    if (nextChar != '\n' && nextChar != -1) {
      istream.setstate(std::ios::failbit);
    }

    if (istream) {
      std::swap(polygon, value);
    }

    return istream;
  }
}
