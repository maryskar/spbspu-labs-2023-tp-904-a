#include "geomfigures.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <IO_structs.hpp>
#include <iofmtguard.hpp>

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
  kotova::Polygon input;
  input.points.reserve(count);
  std::copy_n(std::istream_iterator< kotova::Point >(in), count, std::back_inserter(input.points));
  if (in)
  {
    rhs = input;
  }
  return in;
}
bool kotova::operator==(const Point &lhs, const Point &rhs)
{
  return (lhs.x == rhs.x && lhs.y == rhs.y);
}
bool kotova::operator ==(const Polygon &lhs, const Polygon &rhs)
{
  return std::equal(lhs.points.begin(), lhs.points.end(), rhs.points.begin());
}
int getPoint(const kotova::Point &a, const kotova::Point &b)
{
  return a.x * b.y - a.y * b.x;
}
double kotova::getArea(const Polygon &polygon)
{
  double area = 0.0;
  std::vector< int > arr(polygon.points.size());
  std::transform(polygon.points.begin(), --polygon.points.end(), ++polygon.points.begin(), arr.begin(), getPoint);
  area = std::accumulate(arr.begin(), arr.end(), 0.0);
  area += getPoint(polygon.points.back(), polygon.points.front());
  return std::abs(area * 0.5);
}
