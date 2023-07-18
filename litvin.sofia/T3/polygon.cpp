#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include "iostructures.hpp"
std::istream & litvin::operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry sentry(in);
  size_t num_of_points = 0;
  in >> num_of_points;
  if (!in || num_of_points < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest.points.clear();
  std::copy_n(std::istream_iterator< Point >(in), num_of_points, std::back_inserter(dest.points));
  return in;
}
std::istream & litvin::operator>>(std::istream & in, Point & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> DelimiterIO{'('} >> dest.x >> DelimiterIO{';'} >> dest.y >> DelimiterIO{')'};
}
size_t litvin::size(const Polygon & dest)
{
  return dest.points.size();
}
size_t litvin::calcArea(const Polygon & dest)
{
  size_t res = 0;
}
