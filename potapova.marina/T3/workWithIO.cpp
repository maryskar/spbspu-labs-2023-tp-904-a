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
  if (in.rdbuf()->sgetc() != dest.sign)
  {
    in.setstate(std::ios::failbit);
  }
  else
  {
    in.ignore(1);
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
  in >> std::ws;
  dest.points.clear();
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t num_points = 0;
  if (!(in >> num_points))
  {
    return in;
  }
  if (num_points < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest.points.resize(num_points);
  for (Point& point : dest.points)
  {
    if (in.rdbuf()->sgetc() == '\n')
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    in >> point;
  }
  const char cur_sym = static_cast<char>(in.rdbuf()->sgetc());
  if (cur_sym != '\n' && cur_sym != EOF)
  {
    in.setstate(std::ios_base::failbit);
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

void potapova::handleInvalidCommand(std::istream& in, std::ostream& out)
{
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  out << "<INVALID COMMAND>\n";
}
