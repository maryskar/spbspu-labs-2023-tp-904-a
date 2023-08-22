#include "point-struct.hpp"
#include <algorithm>
#include <iterator>
#include <io-work.hpp>


std::istream & turkin::operator>>(std::istream & in, Point & rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' } >> rhs.x >> DelimiterIO{ ';' } >> rhs.y >> DelimiterIO{ ')' };
  return in;
}

std::istream & turkin::operator>>(std::istream & in, Polygon & rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Polygon input;
  unsigned len = 0;
  in >> len;
  if (len < 3)
  {
    in.setstate(std::ios::failbit);
  }
  input.points.reserve(len);
  
  std::copy_n(std::istream_iterator< Point >(in), len, std::back_inserter(input.points));
  if (in)
  {
    rhs.points.swap(input.points);
  }
  return in;
}
