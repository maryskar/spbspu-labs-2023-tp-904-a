#include "geomfigures.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>

std::istream &operator>>(std::istream &in, kotova::Polygon &rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
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
std::istream &operator>>(std::istream &in, const kotova::Point &rhs);
