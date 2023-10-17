#include "workWithIO.h"
#include <iterator>
#include <algorithm>

std::istream& potapova::operator>>(std::istream& in, potapova::DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char sym = '0';
  in >> sym;
  if (in && (sym != dest.sign))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& potapova::operator>>(std::istream& in, potapova::Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point input_point{0, 0};
  in >> DelimiterIO{'('} >> dest.x >> DelimiterIO{';'} >> dest.y >> DelimiterIO{')'};
  if (in)
  {
    dest = input_point;
  }
  return in;
}

std::ostream& potapova::operator<<(std::ostream& out, const potapova::Point& source)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  return out << '(' << source.x << ';' << source.y << ')';
}

std::istream& potapova::operator>>(std::istream& in, potapova::Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Polygon input_polygon;
  size_t num_points = 0;
  in >> num_points;
  if (num_points < 3)
  {
    in.setstate(std::ios::failbit);
  }
  input_polygon.points.reserve(num_points);
  std::copy_n(std::istream_iterator< Point >(in),
    num_points,
    std::back_inserter(input_polygon.points));
  if (in)
  {
    dest.points.swap(input_polygon.points);
  }
  return in;
}

std::ostream& potapova::operator<<(std::ostream& out, const Polygon& source)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  size_t num_points = source.points.size();
  out << num_points;
  out << ' ';
  std::copy_n(source.points.begin(),
    num_points - 1,
    std::ostream_iterator< Point >(out, " "));
  return out << source.points.back();
}
