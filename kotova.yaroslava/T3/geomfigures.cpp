#include "geomfigures.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <IO_structs.hpp>


std::istream &kotova::operator>>(std::istream &in, kotova::Point &rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = kotova::DelimiterIO;
  in >> del{ '(' } >> rhs.x >> del{ ';' } >> rhs.y >> del{ ')' };
  return in;
}

std::istream &kotova::operator>>(std::istream &in, kotova::Polygon &rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  size_t points = 0;
  kotova::Polygon input;
  in >> points;
  input.points.reserve(points);
  std::copy_n(std::istream_iterator< kotova::Point >(in), points, std::back_inserter(input.points));
  if (in)
  {
    rhs = input;
  }
  return in;
}
std::ostream &kotova::operator<<(std::ostream &out, const Point &rhs)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  return out << '(' << rhs.x << ';' << rhs.y << ')';
}
std::ostream &kotova::operator<<(std::ostream &out, const Polygon &rhs)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  size_t points = rhs.points.size();
  out << points;
  out << ' ';
  std::copy_n(rhs.points.begin(), points - 1, std::ostream_iterator< Point >(out, " "));
  out << rhs.points.back();
  return out;
}
int getPoint(const kotova::Point &a, const kotova::Point &b)
{
  return a.x * b.y - a.y * b.x;
}
double kotova::getArea(const Polygon &polygon)
{
  double area = 0.0;
  std::vector< int > arr(polygon.points.size());
  std::transform(polygon.points.begin(), --polygon.points.end(), ++polygon.points.begin(), std::back_inserter(arr), getPoint);
  area = std::accumulate(arr.begin(), arr.end(), 0.0);
  area += (--polygon.points.end())->x * polygon.points.begin()->y - polygon.points.begin()->x * (--polygon.points.end())->y;
  return std::abs(area * 0.5);
}
