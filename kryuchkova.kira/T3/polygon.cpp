#include "polygon.h"
#include "../common/IOstructs.h"
#include <vector>

namespace kryuchkova
{
  std::istream & operator>>( std::istream & in, Polygon & polygon)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    size_t size = 0;
    in >> size;
    if (!in || size < 3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    polygon.points.clear();
    std::copy_n(std::istream_iterator< Point >(in), size, std::back_inserter(polygon.points));
    return in;
  }
}
