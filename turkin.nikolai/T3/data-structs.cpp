#include "data-structs.hpp"

#include <algorithm>
#include <iterator>
#include <iomanip>
#include <io-work.hpp>

turkin::ReturnType::ReturnType(std::size_t num):
  num_({ .uns=num }),
  type_('u')
{}

turkin::ReturnType::ReturnType(double num):
  num_({ .db=num }),
  type_('d')
{}

std::ostream & turkin::operator<<(std::ostream & out, const ReturnType & rt)
{
  if (rt.type_ == 'u')
  {
    out << rt.num_.uns;
  }
  else if (rt.type_ == 'd')
  {
    out << std::fixed << std::setprecision(1) << rt.num_.db;
  }
  return out;
}

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
