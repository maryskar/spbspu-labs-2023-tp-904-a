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
  auto pointsBeginIt = std::begin(polygon.points);
  auto pointsEndIt = std::end(polygon.points);

  int minX = (*std::min_element(pointsBeginIt, pointsEndIt, isXLess)).x;
  int minY = (*std::min_element(pointsBeginIt, pointsEndIt, isYLess)).y;
  int maxX = (*std::max_element(pointsBeginIt, pointsEndIt, isXLess)).x;
  int maxY = (*std::max_element(pointsBeginIt, pointsEndIt, isYLess)).y;

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

  auto polygonsBeginIt = std::begin(polygons) + 1;
  auto polygonsEndIt = std::end(polygons);
  auto foldFrame = std::bind(getFrameUnion, _1, std::bind(getPolygonFrame, _2));

  return std::accumulate(polygonsBeginIt, polygonsEndIt, firstFrame, foldFrame);
}

bool isPointInFrame(const ganiullin::Point& point,
    const std::pair< ganiullin::Point, ganiullin::Point > frame)
{
  bool isInLeftBorder = frame.first.x <= point.x;
  bool isInRightBorder = frame.second.x >= point.x;
  bool isInTopBorder = frame.first.y <= point.y;
  bool isInBottomBorder = frame.second.y >= point.y;

  return isInLeftBorder && isInRightBorder && isInBottomBorder && isInTopBorder;
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
  std::vector< Point > lhsCopy;
  lhsCopy.reserve(lhs.points.size());
  std::vector< Point > rhsCopy;
  rhsCopy.reserve(lhs.points.size());
  std::vector< bool > areTranslatedPoints;
  areTranslatedPoints.reserve(lhs.points.size());

  auto lhsCopyBeginIt = std::begin(lhsCopy);
  auto lhsCopyEndIt = std::end(lhsCopy);
  auto rhsCopyBeginIt = std::begin(rhsCopy);
  auto rhsCopyEndIt = std::end(rhsCopy);
  auto transBeginIt = std::begin(areTranslatedPoints);
  auto transEndIt = std::end(areTranslatedPoints);

  std::copy(std::begin(lhs.points), std::end(lhs.points), lhsCopyBeginIt);
  std::copy(std::begin(rhs.points), std::end(rhs.points), rhsCopyBeginIt);
  std::sort(lhsCopyBeginIt, lhsCopyEndIt, comparePoints);
  std::sort(rhsCopyBeginIt, rhsCopyEndIt, comparePoints);
  int diffX = lhsCopy[0].x - rhsCopy[0].x;
  int diffY = lhsCopy[0].y - rhsCopy[0].y;

  auto isPointTranslated = std::bind(std::equal_to< Point >{}, _1,
      std::bind(translatePoint, _2, diffX, diffY));

  std::transform(lhsCopyBeginIt, lhsCopyEndIt, rhsCopyBeginIt, transBeginIt,
      isPointTranslated);

  auto isTrue = std::bind(std::logical_and< bool >{}, _1, true);

  return std::all_of(transBeginIt, transEndIt, isTrue);
}

size_t ganiullin::getNumOfVertexes(const Polygon& fig)
{
  return fig.points.size();
}
