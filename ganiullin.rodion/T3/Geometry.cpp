#include "Geometry.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <iterator>  //FIXME: DEBUG
#include <numeric>
#include "TypesIO.h"

using Point = ganiullin::Point;
using Polygon = ganiullin::Polygon;

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
std::istream& ganiullin::operator>>(std::istream& in, Polygon& polygon)
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
std::ostream& ganiullin::operator<<(std::ostream& out, const Polygon& polygon)
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
bool ganiullin::operator==(const Point& first, const Point& second)
{
  return first.x == second.x && first.y == second.y;
}

double getArea(const Point p1, const Point p2, const Point p3)
{
  // Formula uses cross product
  return std::abs((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y)) / 2.0;
}
double ganiullin::getPolygonArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  std::vector< double > areas;
  const Point pivot = polygon.points[0];
  auto firstPointIter = std::begin(polygon.points) + 1;
  auto endPointIter = std::end(polygon.points) - 1;
  auto secondPointIter = firstPointIter + 1;
  double polygonArea = 0;

  auto func = std::bind(getArea, _1, _2, pivot);
  std::transform(firstPointIter, endPointIter, secondPointIter, std::back_inserter(areas), func);

  polygonArea = std::accumulate(std::begin(areas), std::end(areas), 0.0);
  return polygonArea;
}

Point getRightFrameCorner(const Polygon& polygon, std::function< bool(const Point& p1, const Point& p2) > comparator)
{
  Point maxPoint = (*(std::max_element(std::begin(polygon.points), std::end(polygon.points), comparator)));
  return maxPoint;
}
Point getLeftFrameCorner(const Polygon& polygon, std::function< bool(const Point& p1, const Point& p2) > comparator)
{
  Point minPoint = (*(std::min_element(std::begin(polygon.points), std::end(polygon.points), comparator)));
  return minPoint;
}
bool ganiullin::isInFrame(const Polygon& fig, const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;

  auto compPointX = [](const Point& p1, const Point& p2) {
    return p1.x < p2.x;
  };
  auto compPointY = [](const Point& p1, const Point& p2) {
    return p1.y < p2.y;
  };

  std::vector< Point > temp;
  temp.reserve(polygons.size());

  std::transform(std::begin(polygons), std::end(polygons), std::begin(temp),
    std::bind(getRightFrameCorner, _1, compPointX));
  const int maxX = (*(std::max_element(std::begin(temp), std::end(temp), compPointX))).x;

  std::transform(std::begin(polygons), std::end(polygons), std::begin(temp),
    std::bind(getRightFrameCorner, _1, compPointY));
  const int maxY = (*(std::max_element(std::begin(temp), std::end(temp), compPointY))).y;

  std::transform(std::begin(polygons), std::end(polygons), std::begin(temp),
    std::bind(getLeftFrameCorner, _1, compPointX));
  const int minX = (*(std::min_element(std::begin(temp), std::end(temp), compPointX))).x;

  std::transform(std::begin(polygons), std::end(polygons), std::begin(temp),
    std::bind(getLeftFrameCorner, _1, compPointY));
  const int minY = (*(std::min_element(std::begin(temp), std::end(temp), compPointY))).y;

  auto isPointInFrame = [&](const Point& point) {
    return point.x <= maxX && point.x >= minX && point.y <= maxY && point.y >= minY;
  };
  return std::all_of(std::begin(fig.points), std::end(fig.points), isPointInFrame);
}

bool isSame(const Polygon& fig, const Polygon& other)
{
  if (fig.points.size() != other.points.size()) {
    return false;
  }
  std::vector< Point > first;
  first.reserve(fig.points.size());
  std::vector< Point > second;
  first.reserve(other.points.size());

  auto comparePoints = [](const Point& p1, const Point& p2) {
    if (p1.x == p2.x) {
      return p1.y < p2.y;
    }
    return p1.x < p2.x;
  };
  std::copy(std::begin(fig.points), std::end(fig.points), std::back_inserter(first));
  std::copy(std::begin(other.points), std::end(other.points), std::back_inserter(second));
  std::sort(std::begin(first), std::end(first), comparePoints);
  std::sort(std::begin(second), std::end(second), comparePoints);

  int diffX = first[0].x - second[0].x;
  int diffY = first[0].y - second[0].y;
  std::for_each(std::begin(second), std::end(second), [&](Point& point) {  // FIXME: rewrite without std::for_each()
    point.x += diffX;
    point.y += diffY;
  });
  return first == second;
}
size_t ganiullin::countSame(const Polygon& fig, const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;
  return std::count_if(std::begin(polygons), std::end(polygons), std::bind(isSame, _1, fig));
}
size_t ganiullin::getNumOfVertexes(const ganiullin::Polygon& fig)
{
  return fig.points.size();
}
