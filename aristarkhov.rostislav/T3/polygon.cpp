#include "polygon.h"
#include <iostruct.h>

namespace aristarkhov
{
  std::istream& operator>>(std::istream& in, Point& point)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    in >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'} >> point.y >> DelimiterIO{')'};
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    size_t inpNum = 0;
    in >> inpNum;

    if (inpNum < 3)
    {
      in.setstate(std::ios::failbit);
    }

    Polygon newData;
    newData.points.reserve(inpNum);
    std::copy_n(std::istream_iterator< Point >(in), inpNum, std::back_inserter(newData.points));

    if (in)
    {
      dest.points.swap(newData.points);
    }

    return in;
  }
}
