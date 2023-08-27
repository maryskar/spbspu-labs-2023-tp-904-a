#include "polygon.h"
#include <iterator>
#include <algorithm>
#include <iotypes.h>
#include <iofmtguard.h>

std::istream &fesenko::operator>>(std::istream &in, Polygon &rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  Polygon input;
  size_t points = 0;
  in >> points;
  if (points < 3) {
    in.setstate(std::ios::failbit);
  }
  input.points.reserve(points);
  std::copy_n(std::istream_iterator< Point >(in),
    points,
    std::back_inserter(input.points));
  if (in) {
    rhs.points.swap(input.points);
  }
  return in;
}
