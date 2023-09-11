#include "polygon.h"
#include "../common/IOstructs.h"
#include <vector>
#include <algorithm>
#include <numeric>

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

  int counter(const Point & lhs, const Point & rhs)
  {
    return lhs.x * rhs.y - rhs.x * lhs.y;
  }

  double getArea(const Polygon & polygon)
  {
    double area = 0.0;
    std::vector< int > areas;
    auto begin = polygon.points.begin();
    auto end = polygon.points.end();
    std::transform(begin, --end, ++begin, std::back_inserter(areas), counter);
    area = std::accumulate(areas.begin(), areas.end(), 0.0);
    area += ((--end)->x * begin->y - begin->x * (--end)->y) * 0.5;
    return abs(area);
  }
}
