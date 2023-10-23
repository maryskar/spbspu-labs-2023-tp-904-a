#include "workWithIO.h"
#include <iterator>
#include <algorithm>
#include <limits>

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
  in >> DelimiterIO{'('} >> dest.x >> DelimiterIO{';'} >> dest.y >> DelimiterIO{')'};
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
  dest.points.clear();
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t num_points = 0;
  in >> num_points;
  if (num_points < 3)
  {
    in.setstate(std::ios::failbit);
  }
  dest.points.reserve(num_points);
  std::copy_n(std::istream_iterator< Point >(in),
    num_points,
    std::back_inserter(dest.points));
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

void potapova::handleInvalidCommand(std::istream& in, std::ostream& out)
{
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  out << "<INVALID COMMAND>\n";
}
