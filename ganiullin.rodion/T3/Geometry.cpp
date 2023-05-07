#include "Geometry.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include "TypesIO.h"

using Point = ganiullin::Point;

std::istream& ganiullin::operator>>(std::istream& in, Point& point)
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
  using inIter = std::istream_iterator< Point >;
  size_t vertexNum = 0;
  in >> vertexNum;
  std::vector< Point > vertices;
  std::copy_n(inIter(in), vertexNum, std::back_inserter(vertices));
  if (in) {
    polygon.points = vertices;
  }
  return in;
}
std::ostream& ganiullin::operator<<(std::ostream& out, const Point& point)
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
  auto outIter = std::ostream_iterator< Point >(out, " ");
  out << polygon.points.size() << ' ';
  std::copy(std::begin(polygon.points), std::end(polygon.points), outIter);
  return out;
}
double ganiullin::getArea(const Point p1, const Point p2, const Point p3)
{
  // Formaula uses cross product
  return std::abs((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y)) / 2.0;
}
double ganiullin::getPolygonArea(const ganiullin::Polygon& polygon)
{
  using namespace std::placeholders;
  std::vector< double > areas;
  const Point pivot = polygon.points[0];
  auto firstPointIter = std::begin(polygon.points) + 1;
  auto endPointIter = std::end(polygon.points) - 1;
  auto secondPointIter = firstPointIter + 1;
  double polygonArea = 0;

  auto func = std::bind(ganiullin::getArea, _1, _2, pivot);
  std::transform(firstPointIter, endPointIter, secondPointIter, std::back_inserter(areas), func);

  std::for_each(std::begin(areas), std::end(areas), [&](double area) {
    polygonArea += area;
  });
  return polygonArea;
}
