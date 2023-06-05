#include "Geometry.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include "TypesIO.h"

bool isXLess(const ganiullin::Point& p1, const ganiullin::Point& p2)
{
  return p1.x < p2.x;
}
bool isYLess(const ganiullin::Point& p1, const ganiullin::Point& p2)
{
  return p1.y < p2.y;
}
std::pair< ganiullin::Point, ganiullin::Point > getFrameUnion(
    const std::pair< ganiullin::Point, ganiullin::Point >& lhs,
    const std::pair< ganiullin::Point, ganiullin::Point >& rhs)
{
  int minX = std::min< int >(lhs.first.x, rhs.first.x);
  int minY = std::min< int >(lhs.first.y, rhs.first.y);
  int maxX = std::max< int >(lhs.second.x, rhs.second.x);
  int maxY = std::max< int >(lhs.second.y, rhs.second.y);
  return {{minX, minY}, {maxX, maxY}};
}
bool comparePoints(const ganiullin::Point& p1, const ganiullin::Point& p2)
{
  if (p1.x == p2.x) {
    return p1.y < p2.y;
  }
  return p1.x < p2.x;
};

std::istream& ganiullin::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  using delim = DelimiterIO;
  int x = 0, y = 0;
  in >> delim{'('} >> x >> delim{';'} >> y >> delim{')'};
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
  if (vertexNum < 3) {
    in.setstate(std::ios::failbit);
  }
  std::vector< Point > vertices;
  vertices.reserve(vertexNum);
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

double getTriangleArea(const ganiullin::Point p1, const ganiullin::Point p2,
    const ganiullin::Point p3)
{
  return std::abs(
             (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y)) /
         2.0;
}
double ganiullin::getArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  std::vector< double > areas;
  areas.reserve(polygon.points.size() - 2);
  const Point pivot = polygon.points[0];

  std::transform(std::begin(polygon.points) + 1, std::end(polygon.points) - 1,
      std::begin(polygon.points) + 2, std::back_inserter(areas),
      std::bind(getTriangleArea, _1, _2, pivot));
  return std::accumulate(std::begin(areas), std::end(areas), 0.0);
}

std::pair< ganiullin::Point, ganiullin::Point > getPolygonFrame(
    const ganiullin::Polygon& polygon)
{
  int minX = (*std::min_element(std::begin(polygon.points),
                  std::end(polygon.points), isXLess))
                 .x;
  int minY = (*std::min_element(std::begin(polygon.points),
                  std::end(polygon.points), isYLess))
                 .y;
  int maxX = (*std::max_element(std::begin(polygon.points),
                  std::end(polygon.points), isXLess))
                 .x;
  int maxY = (*std::max_element(std::begin(polygon.points),
                  std::end(polygon.points), isYLess))
                 .y;
  return {{minX, minY}, {maxX, maxY}};
}
std::pair< ganiullin::Point, ganiullin::Point > ganiullin::getFrame(
    const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;
  if (polygons.size() == 0) {
    throw std::logic_error("Polygons vector should not be empty");
  }
  std::pair< Point, Point > firstFrame = getPolygonFrame(polygons[0]);
  return std::accumulate(std::begin(polygons) + 1, std::end(polygons),
      firstFrame, std::bind(getFrameUnion, _1, std::bind(getPolygonFrame, _2)));
}

bool isPointInFrame(const ganiullin::Point& point,
    const std::pair< ganiullin::Point, ganiullin::Point > frame)
{
  return point.x >= frame.first.x && point.x <= frame.second.x &&
         point.y >= frame.first.y && point.y <= frame.second.y;
}

bool ganiullin::isInFrame(const Polygon& fig,
    const std::pair< Point, Point >& frame)
{
  using namespace std::placeholders;
  return std::all_of(std::begin(fig.points), std::end(fig.points),
      std::bind(isPointInFrame, _1, frame));
}
ganiullin::Point translatePoint(const ganiullin::Point& point, int x, int y)
{
  return ganiullin::Point{point.x + x, point.y + y};
}

bool ganiullin::isSame(const Polygon& lhs, const Polygon& rhs)
{
  using namespace std::placeholders;
  if (lhs.points.size() != rhs.points.size()) {
    return false;
  }
  std::vector< Point > first;
  first.reserve(lhs.points.size());
  std::vector< Point > second;
  second.reserve(lhs.points.size());
  std::vector< bool > areTranslatedPoints;
  areTranslatedPoints.reserve(lhs.points.size());

  std::copy(std::begin(lhs.points), std::end(lhs.points),
      std::back_inserter(first));
  std::copy(std::begin(rhs.points), std::end(rhs.points),
      std::back_inserter(second));
  std::sort(std::begin(first), std::end(first), comparePoints);
  std::sort(std::begin(second), std::end(second), comparePoints);
  int diffX = first[0].x - second[0].x;
  int diffY = first[0].y - second[0].y;
  std::transform(std::begin(first), std::end(first), std::begin(second),
      std::back_inserter(areTranslatedPoints),
      std::bind(std::equal_to< Point >{}, _1,
          std::bind(translatePoint, _2, diffX, diffY)));
  return std::all_of(std::begin(areTranslatedPoints),
      std::end(areTranslatedPoints),
      std::bind(std::logical_and< bool >{}, _1, true));
}

size_t ganiullin::getNumOfVertexes(const Polygon& fig)
{
  return fig.points.size();
}
