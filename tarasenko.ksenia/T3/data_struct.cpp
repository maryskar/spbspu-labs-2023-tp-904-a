#include "data_struct.h"
#include <structs_io.h>
#include <iofmtguard.h>

std::ostream& tarasenko::operator<<(std::ostream& out, const Polygon& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << '(' << src.points[0].x << ";" << src.points[0].y << ')';
  for (size_t i = 1; i < src.points.size(); ++i)
  {
    out << " " << '(' << src.points[i].x << ";" << src.points[i].y << ')';
  }
  return out;
}

std::istream& tarasenko::operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Polygon input;
  {
    using sep = DelimiterIO;

    size_t n;
    in >> n;
    for (size_t i = 0; i < n; i++)
    {
      Point p;
      in >> sep{'('} >> p.x >> sep{';'} >> p.y >> sep{')'};
      input.points.push_back(p);
    }
  }
  if (in)
  {
    dest = input;
  }
  return in;
}
