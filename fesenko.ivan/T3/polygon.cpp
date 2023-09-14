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
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    in.setstate(std::ios::failbit);
    return in;
  }
  input.points.reserve(points);
  std::copy_n(std::istream_iterator< Point >(in),
    points,
    std::back_inserter(input.points));
  if (!in) {
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    return in;
  }
  rhs.points.swap(input.points);
  std::string checker;
  std::getline(in, checker);
  if (checker.find_first_not_of(' ') != std::string::npos) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream &fesenko::operator<<(std::ostream &out, const Polygon &rhs)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  iofmtguard fmtguard(out);
  size_t points = rhs.points.size();
  out << points;
  std::copy_n(rhs.points.begin(),
    points - 1,
    std::ostream_iterator< Point >(out << ' ', " ")
  );
  return out << rhs.points.back();
}
