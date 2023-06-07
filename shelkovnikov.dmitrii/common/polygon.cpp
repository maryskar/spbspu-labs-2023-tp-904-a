#include "polygon.h"
#include <iterator>
#include <algorithm>
std::istream &dimkashelk::operator>>(std::istream &in, dimkashelk::Polygon &polygon)
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
  std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(polygon.points));
  return in;
}
