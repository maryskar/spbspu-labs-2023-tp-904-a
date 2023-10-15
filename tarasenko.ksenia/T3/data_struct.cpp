#include "data_struct.h"
#include <algorithm>
#include <iterator>
#include <structs_io.h>
#include <iofmtguard.h>

std::istream& tarasenko::operator>>(std::istream& in, Point& dest)
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

std::ostream& tarasenko::operator<<(std::ostream& out, const Point& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  return out << '(' << src.x << ";" << src.y << ')';
}

std::ostream& tarasenko::operator<<(std::ostream& out, const Polygon& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  size_t n = src.points.size();
  out << n << " ";
  std::copy_n(src.points.begin(), n - 1, std::ostream_iterator< Point >(out, " "));
  return out << src.points.back();
}

std::istream& tarasenko::operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Polygon input;
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(input.points));
  if (in)
  {
    dest = input;
  }
  return in;
}
