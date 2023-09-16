#include "polygon.h"
#include "scopeGuard.h"
#include "typesIO.h"

std::istream &gudkov::operator>>(std::istream &in, Point &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  iofmtguard fmtguard(in);

  in.unsetf(std::ios_base::skipws);

  Point input;
  {
    in >> DelimiterExpIO{ '(' };
    in >> input.x;
    in >> DelimiterExpIO{ ';' };
    in >> input.y;
    in >> DelimiterExpIO{ ')' };
  }

  if (in)
  {
    dest = input;
  }

  return in;
}

std::ostream &gudkov::operator<<(std::ostream &out, const Point &dest)
{
  std::ostream::sentry sentry(out);

  if (!sentry)
  {
    return out;
  }

  out << '(';
  out << dest.x;
  out << ';';
  out << dest.y;
  out << ')';

  return out;
}

std::istream &gudkov::operator>>(std::istream &in, Polygon &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  iofmtguard fmtguard(in);

  in.unsetf(std::ios_base::skipws);

  Polygon input;

  {
    size_t n = 0;
    in >> n;

    if (in)
    {
      input.points.resize(n);

      for (size_t i = 0; i < n; ++i)
      {
        in >> DelimiterExpIO{ ' ' };
        in >> input.points[i];
      }
    }
  }

  if (in)
  {
    dest = input;

    in >> DelimiterExpIO{ '\n' };

    if (in.eof())
    {
      in.clear();
    }
  }

  return in;
}

std::ostream &gudkov::operator<<(std::ostream &out, const Polygon &dest)
{
  std::ostream::sentry sentry(out);

  if (!sentry)
  {
    return out;
  }

  std::cout << dest.points.size();
  for (size_t i = 0; i < dest.points.size(); ++i)
  {
    std::cout << ' ' << dest.points[i];
  }

  return out;
}
