#include "polygon.hpp"
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
  return in >> DelimiterIO{'('} >> dest.x >> DelimiterIO{';'} >> dest.y >> DelimiterIO{')'};
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
  dest.data.clear();
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
  std::transform(pol.data.begin(), --pol.data.end(), ++pol.data.begin(), std::back_inserter(areas), trans);
  area = std::accumulate(areas.begin(), areas.end(), 0.0);
  area += (--pol.data.end())->x * pol.data.begin()->y - pol.data.begin()->x * (--pol.data.end())->y;
  area = 0.5 * std::abs(area);
  return area;
}

bool chemodurov::operator==(const Polygon & lhs, const Polygon & rhs)
{
  return (size(lhs) == size(rhs)) && (lhs.data == rhs.data);
}

bool chemodurov::operator==(const Point & lhs, const Point & rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool chemodurov::operator!=(const Point & lhs, const Point & rhs)
{
  return !(lhs == rhs);
}

bool chemodurov::operator!=(const Polygon & lhs, const Polygon & rhs)
{
  return !(lhs == rhs);
}
