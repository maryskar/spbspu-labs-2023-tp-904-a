#include "polygon.hpp"
#include <sstream>
#include <iterator>
#include <algorithm>
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
