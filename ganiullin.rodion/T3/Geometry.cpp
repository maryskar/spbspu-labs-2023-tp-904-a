#include "Geometry.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include "TypesIO.h"

std::istream& ganiullin::operator>>(std::istream& in, ganiullin::Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  using delim = ganiullin::DelimiterIO;
  int x = 0, y = 0;
  in >> delim {'('} >> x >> delim {';'} >> y >> delim {')'};
  if (in) {
    point.x = x;
    point.y = y;
  }
  return in;
}
std::istream& ganiullin::operator>>(std::istream& in, ganiullin::Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  using inIter = std::istream_iterator< ganiullin::Point >;
  size_t vertexNum = 0;
  in >> vertexNum;
  std::vector< Point > vertices;
  std::copy_n(inIter(in), vertexNum, std::back_inserter(vertices));
  if (in) {
    polygon.points = vertices;
  }
  return in;
}
std::ostream& ganiullin::operator<<(std::ostream& out, const ganiullin::Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  return out << '(' << point.x << ';' << point.y << ')';
}

std::ostream& ganiullin::operator<<(std::ostream& out, const ganiullin::Polygon& polygon)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  auto outIter = std::ostream_iterator< ganiullin::Point >(out, " ");
  out << polygon.points.size() << ' ';
  std::copy(std::begin(polygon.points), std::end(polygon.points), outIter);
  return out;
}
