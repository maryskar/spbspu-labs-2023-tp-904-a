#include "helpFunctions.h"
#include <algorithm>
#include <functional>
#include <cmath>
bool avdeeva::isOdd(const Polygon & pol)
{
  return (size(pol) % 2);
}
bool avdeeva::isEven(const Polygon & pol)
{
  return !(isOdd(pol));
}
bool avdeeva::isNumOfVerts(const Polygon & pol, size_t num)
{
  return size(pol) == num;
}
bool avdeeva::compArea(const Polygon & lhs, const Polygon & rhs)
{
  return (getArea(lhs) < getArea(rhs));
}
bool avdeeva::compSize(const Polygon & lhs, const Polygon & rhs)
{
  return (lhs.points.size() < rhs.points.size());
}
double avdeeva::getDist(const Point & lhs, const Point & rhs)
{
  return std::sqrt(std::pow(std::abs(lhs.x - rhs.x), 2) + std::pow(std::abs(lhs.y - rhs.y), 2));
}
bool avdeeva::isRightTriangle(const Point & first, const Point & second, const Point & third)
{
  double side12 = getDist(first, second);
  double side23 = getDist(second, third);
  double side13 = getDist(first, third);
  double checkSide = std::sqrt(std::pow(side12, 2) + std::pow(side23, 2));
  return checkSide == side13;
}
bool avdeeva::checkTriangle(Point & first, Point & second, const Point & third)
{
  bool isRight = isRightTriangle(first, second, third);
  first = second;
  second = third;
  return isRight;
}
bool avdeeva::isRightshape(const Polygon & polygon)
{
  Point first = polygon.points.at(polygon.points.size() - 2);
  Point second = polygon.points.at(polygon.points.size() - 1);
  auto begin = polygon.points.begin();
  auto end = polygon.points.end();
  using namespace std::placeholders;
  auto checkPoint = std::bind(checkTriangle, first, second, _1);
  size_t countRightTriangles = std::count_if(begin, end, checkPoint);
  return (counterRight > 0);
}
avdeeva::Point avdeeva::minPoint(const Polygon & polygon)
{
  auto begin = polygon.points.begin();
  auto end = polygon.points.end();
  int minX = std::min_element(begin, end, compX)->x;
  int minY = std::min_element(begin, end, compY)->y;
  Point minPoint{minX, minY};
  return minPoint;
}
avdeeva::Point avdeeva::maxPoint(const Polygon & polygon)
{
  auto begin = polygon.points.begin();
  auto end = polygon.points.end();
  int maxX = std::max_element(begin, end, compX)->x;
  int maxY = std::max_element(begin, end, compY)->y;
  Point maxPoint{maxX, maxY};
  return maxPoint;
}
bool avdeeva::compMinX(const Polygon & lhs, const Polygon & rhs)
{
  return minPoint(lhs).x < minPoint(rhs).x;
}
bool avdeeva::compMaxX(const Polygon & lhs, const Polygon & rhs)
{
  return maxPoint(lhs).x < maxPoint(rhs).x;
}
bool avdeeva::compMinY(const Polygon & lhs, const Polygon & rhs)
{
  return minPoint(lhs).y < minPoint(rhs).y;
}
bool avdeeva::compMaxY(const Polygon & lhs, const Polygon & rhs)
{
  return maxPoint(lhs).y < maxPoint(rhs).y;
}
avdeeva::Polygon avdeeva::createFrame(const std::deque< Polygon > & polygons)
{
  Polygon frame;
  auto begin = polygons.begin();
  auto end = polygons.end();
  int minX = minPoint(*std::min_element(begin, end, compMinX)).x;
  int minY = minPoint(*std::min_element(begin, end, compMinY)).y;
  int maxX = maxPoint(*std::max_element(begin, end, compMaxX)).x;
  int maxY = maxPoint(*std::max_element(begin, end, compMaxY)).y;
  frame.points.push_back(Point{minX, minY});
  frame.points.push_back(Point{maxX, maxY});
  frame.points.push_back(Point{maxX, minY});
  frame.points.push_back(Point{minX, maxY});
  return frame;
}
bool avdeeva::isLessPoint(const Point & lhs, const Point & rhs)
{
  return (lhs.x <= rhs.x) && (lhs.y <= rhs.y);
}
bool avdeeva::isInFrame(const Polygon & polygon, const Polygon & frame)
{
  Point minPol = minPoint(polygon);
  Point maxPol = maxPoint(polygon);
  Point minFrame = minPoint(frame);
  Point maxFrame = maxPoint(frame);
  bool minPoints = isLessPoint(minFrame, minPol);
  bool maxPoints = isLessPoint(maxPol, maxFrame);
  return minPoints && maxPoints;
}
