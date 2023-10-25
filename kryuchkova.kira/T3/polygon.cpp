#include "polygon.h"
#include <IOstructs.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <limits>

namespace kryuchkova
{
  std::istream & operator>>(std::istream & in, Polygon & polygon)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    size_t size = 0;
    in >> size;
    constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
    if (!in || size < 3)
    {
      in.ignore(max_size, '\n');
      in.setstate(std::ios::failbit);
      return in;
    }
    polygon.points.clear();
    std::copy_n(std::istream_iterator< Point >(in), size, std::back_inserter(polygon.points));
    if (!in)
    {
      in.ignore(max_size, '\n');
      return in;
    }
    std::string endOfLine;
    std::getline(in, endOfLine);
    if (endOfLine.find_first_not_of(' ') != std::string::npos)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
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
    std::transform(polygon.points.begin(), --polygon.points.end(), ++polygon.points.begin(), std::back_inserter(areas), counter);
    area = std::accumulate(areas.begin(), areas.end(), 0.0);
    area += ((--polygon.points.end())->x * polygon.points.begin()->y - polygon.points.begin()->x * (--polygon.points.end())->y);
    area = std::abs(area) / 2;
    return area;
  }
}
