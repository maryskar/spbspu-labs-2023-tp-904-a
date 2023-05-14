#include "Polygon.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>

std::istream & malaya::operator>>(std::istream & in, SeparatorPointIO && separator)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  char input = '0';
  in >> input;
  if (in && (input != separator.sep))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & malaya::operator>>(std::istream & in, Point & point)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  in >> SeparatorPointIO{'('};
  in >> point.x;
  in >> SeparatorPointIO{';'};
  in >> point.y;
  in >> SeparatorPointIO{')'};
  return in;
}

std::istream & malaya::operator>>(std::istream & in, Polygon & polygon)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  using inIter = std::istream_iterator< malaya::Point >;
  int pointNumber = 0;
  in >> pointNumber;
  std::copy_n(inIter(in), pointNumber, std::back_inserter(polygon.points));
  return in;
}