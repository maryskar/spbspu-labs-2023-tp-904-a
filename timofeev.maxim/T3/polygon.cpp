#include "polygon.h"
#include <iterator>
#include <algorithm>
#include <IofGuard.h>
#include <DataStruct.h>
namespace timofeev
{
  std::istream &operator>>(std::istream &in, Polygon &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    using inIter = std::istream_iterator< Point >;
    size_t countPoint = 0;
    in >> countPoint;
    if (countPoint < 3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    dest.points.clear();
    std::copy_n(inIter(in), countPoint, std::back_inserter(dest.points));
    return in;
  }

  std::istream &operator>>(std::istream &in, Point &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    using sep = DelimiterIO;
    in >> sep{'('} >> dest.x >> sep{';'} >> dest.y >> sep{')'};
    return in;
  }
  size_t size(const Polygon &dest)
  {
    return dest.points.size();
  }
}
