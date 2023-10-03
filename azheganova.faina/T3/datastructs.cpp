#include "datastructs.h"
#include <algorithm>
#include <numeric>
#include <limits>
#include <functional>
#include <iterator>
#include <iotypes.h>

std::istream & azheganova::operator>>(std::istream & in, Point & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' } >> dest.y >> DelimiterIO{ ')' };
  return in;
}

std::istream & azheganova::operator>>(std::istream & in, Polygon & dest)
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
  Polygon polygon;
  std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(polygon.points));
  if (in)
  {
    dest = polygon;
  }
  return in;
}

bool azheganova::operator==(const Point & first, const Point & second)
{
  return (first.x == second.x) && (first.y == second.y);
}

bool azheganova::operator==(const Polygon & first, const Polygon & second)
{
  auto firstBegin = first.points.begin();
  auto firstEnd = first.points.end();
  auto secondBegin = second.points.begin();
  bool checkEqual = std::equal(firstBegin, firstEnd, secondBegin);
  return first.points.size() == second.points.size() && checkEqual;
}


