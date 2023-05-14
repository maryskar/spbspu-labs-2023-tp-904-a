#include "polygon.hpp"
#include <sstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <IO-structs.hpp>

std::istream & chemodurov::operator>>(std::istream & in, Point & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> DelimiterIO{' '} >> DelimiterIO{'('} >> dest.x >> DelimiterIO{';'} >> dest.y >> DelimiterIO{')'};
}

std::istream & chemodurov::operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t num_of_points = 0;
  in >> num_of_points;
  if (!in || num_of_points < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::copy_n(std::istream_iterator< Point >(in), num_of_points, std::back_inserter(dest.data));
  return in;
}

size_t chemodurov::size(const Polygon & pol)
{
  return pol.data.size();
}

namespace chemodurov
{
  int trans(const Point & lhs, const Point & rhs)
  {
    return lhs.x * rhs.y - rhs.x * lhs.y;
  }
}

double chemodurov::calcArea(const Polygon & pol)
{
  double area = 0.0;
  std::vector< int > areas;
  areas.reserve(size(pol));
  std::transform(pol.data.begin(), --pol.data.end(), ++pol.data.begin(), areas.begin(), trans);
  *(--areas.end()) = (--pol.data.end())->x * pol.data.begin()->y - pol.data.begin()->x * (--pol.data.end())->y;
  area = std::accumulate(areas.begin(), areas.end(), 0.0);
  area /= 2;
  return area;
}
