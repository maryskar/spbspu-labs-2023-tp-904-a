#include "Geometry.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include "TypesIO.h"

std::istream& ganiullin::operator>>(std::istream& in, ganiullin::Point& point)
{
  if (!in) {
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
  if (!in) {
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
