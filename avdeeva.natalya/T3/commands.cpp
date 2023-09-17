#include "commands.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
namespace
{
  bool isOdd(const avdeeva::Polygon & pol)
  {
    return (pol.points.size() % 2);
  }
  bool isEven(const avdeeva::Polygon & pol)
  {
    return !(isOdd(pol));
  }
  bool isNumOfVerts(const avdeeva::Polygon & pol, size_t num)
  {
    return pol.points.size() == num;
  }
  template< typename Pred >
  double calcArea(const std::deque< avdeeva::Polygon > & polygons, Pred p)
  {
    std::deque < avdeeva::Polygon > filtPolygons;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(filtPolygons), p);
    std::deque< double > values(filtPolygons.size());
    std::transform(filtPolygons.begin(), filtPolygons.end(), values.begin(), avdeeva::getArea);
    return std::accumulate(values.begin(), values.end(), 0.0);
  }
}
double avdeeva::calcAreaOdd(const std::deque< Polygon > & polygons)
{
  return calcArea(polygons, isOdd);
}
double avdeeva::calcAreaEven(const std::deque< Polygon > & polygons)
{
  return calcArea(polygons, isEven);
}
double avdeeva::calcAreaMean(const std::deque< Polygon > & polygons)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("Empty deque of polygons");
  }
  std::deque< double > values(polygons.size());
  std::transform(polygons.begin(), polygons.end(), values.begin(), getArea);
  double value = std::accumulate(values.begin(), values.end(), 0.0);
  double res = value / polygons.size();
  return res;
}
double avdeeva::calcAreaVerts(const std::deque< Polygon > & polygons, size_t num)
{
  using namespace std::placeholders;
  auto pred = std::bind(isNumOfVerts, _1, num);
  return calcArea(polygons, pred);
}
namespace
{
  template< typename Pred >
  size_t count(const std::deque< avdeeva::Polygon > & polygons, Pred p)
  {
    return std::count_if(polygons.begin(), polygons.end(), p);
  }
}
size_t avdeeva::countEven(const std::deque< Polygon > & polygons)
{
  return count(polygons, isEven);
}
size_t avdeeva::countOdd(const std::deque< Polygon > & polygons)
{
  return count(polygons, isOdd);
}
size_t avdeeva::countIsNumVertexes(const std::deque< Polygon > & polygons, size_t num)
{
  using namespace std::placeholders;
  auto pred = std::bind(isNumOfVerts, _1, num);
  return count(polygons, pred);
}
namespace
{
  bool compArea(const avdeeva::Polygon & lhs, const avdeeva::Polygon & rhs)
  {
    return (getArea(lhs) < getArea(rhs));
  }
  bool compSize(const avdeeva::Polygon & lhs, const avdeeva::Polygon & rhs)
  {
    return (lhs.points.size() < rhs.points.size());
  }
  size_t size(const avdeeva::Polygon & pol)
  {
    return pol.points.size();
  }
  template< typename T, typename Func, typename Comp >
  T findMax(const std::deque< avdeeva::Polygon > & polygons, Comp comp, Func func)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Empty deque of polygons");
    }
    return func(*std::max_element(polygons.begin(), polygons.end(), comp));
  }
}
double avdeeva::findMaxArea(const std::deque< Polygon > & polygons)
{
  return findMax< double >(polygons, compArea, getArea);
}
size_t avdeeva::findMaxVerts(const std::deque< Polygon > & polygons)
{
  return findMax< size_t >(polygons, compSize, size);
}
namespace
{
  template< typename T, typename Func, typename Comp >
  T findMin(const std::deque< avdeeva::Polygon > & polygons, Comp comp, Func func)
  {
    if (polygons.empty())
    {
      throw std::logic_error("Empty deque of polygons");
    }
    return func(*std::min_element(polygons.begin(), polygons.end(), comp));
  }
}
double avdeeva::findMinArea(const std::deque< Polygon > & polygons)
{
  return findMin< double >(polygons, compArea, getArea);
}
size_t avdeeva::findMinVerts(const std::deque< Polygon > & polygons)
{
  return findMin< size_t >(polygons, compSize, size);
}
namespace
{
  double getDist(const avdeeva::Point & lhs, const avdeeva::Point & rhs)
  {
    return std::sqrt(std::pow(std::abs(lhs.x - rhs.x), 2) + std::pow(std::abs(lhs.y - rhs.y), 2));
  }
  bool isRightTriangle(const avdeeva::Point & first, const avdeeva::Point & second, const avdeeva::Point & third)
  {
    double side12 = getDist(first, second);
    double side23 = getDist(second, third);
    double side13 = getDist(first, third);
    double checkSide = std::sqrt(std::pow(side12, 2) + std::pow(side23, 2));
    return checkSide == side13;
  }
  bool checkTriangle(avdeeva::Point & first, avdeeva::Point & second, const avdeeva::Point & third)
  {
    bool isRight = isRightTriangle(first, second, third);
    first = second;
    second = third;
    return isRight;
  }
  bool isRightshape(const avdeeva::Polygon & polygon)
  {
    avdeeva::Point first = polygon.points.at(polygon.points.size() - 2);
    avdeeva::Point second = polygon.points.at(polygon.points.size() - 1);
    auto begin = polygon.points.begin();
    auto end = polygon.points.end();
    using namespace std::placeholders;
    auto checkPoint = std::bind(checkTriangle, first, second, _1);
    size_t countRightTriangles = std::count_if(begin, end, checkPoint);
    return (countRightTriangles > 0);
  }
}
size_t avdeeva::countRightShapes(const std::deque< Polygon > & polygons)
{
  int res = std::count_if(polygons.begin(), polygons.end(), isRightshape);
  return res;
}
namespace
{
  bool compX(const avdeeva::Point & lhs, const avdeeva::Point & rhs)
  {
    return (lhs.x < rhs.x);
  }
  bool compY(const avdeeva::Point & lhs, const avdeeva::Point & rhs)
  {
    return (lhs.y < rhs.y);
  }
  avdeeva::Point minPoint(const avdeeva::Polygon & polygon)
  {
    auto begin = polygon.points.begin();
    auto end = polygon.points.end();
    int minX = std::min_element(begin, end, compX)->x;
    int minY = std::min_element(begin, end, compY)->y;
    avdeeva::Point minPoint{minX, minY};
    return minPoint;
  }
  avdeeva::Point maxPoint(const avdeeva::Polygon & polygon)
  {
    auto begin = polygon.points.begin();
    auto end = polygon.points.end();
    int maxX = std::max_element(begin, end, compX)->x;
    int maxY = std::max_element(begin, end, compY)->y;
    avdeeva::Point maxPoint{maxX, maxY};
    return maxPoint;
  }
  bool compMinX(const avdeeva::Polygon & lhs, const avdeeva::Polygon & rhs)
  {
    return minPoint(lhs).x < minPoint(rhs).x;
  }
  bool compMaxX(const avdeeva::Polygon & lhs, const avdeeva::Polygon & rhs)
  {
    return maxPoint(lhs).x < maxPoint(rhs).x;
  }
  bool compMinY(const avdeeva::Polygon & lhs, const avdeeva::Polygon & rhs)
  {
    return minPoint(lhs).y < minPoint(rhs).y;
  }
  bool compMaxY(const avdeeva::Polygon & lhs, const avdeeva::Polygon & rhs)
  {
    return maxPoint(lhs).y < maxPoint(rhs).y;
  }
  avdeeva::Polygon createFrame(const std::deque< avdeeva::Polygon > & polygons)
  {
    avdeeva::Polygon frame;
    auto begin = polygons.begin();
    auto end = polygons.end();
    int minX = minPoint(*std::min_element(begin, end, compMinX)).x;
    int minY = minPoint(*std::min_element(begin, end, compMinY)).y;
    int maxX = maxPoint(*std::max_element(begin, end, compMaxX)).x;
    int maxY = maxPoint(*std::max_element(begin, end, compMaxY)).y;
    frame.points.push_back(avdeeva::Point{minX, minY});
    frame.points.push_back(avdeeva::Point{maxX, maxY});
    frame.points.push_back(avdeeva::Point{maxX, minY});
    frame.points.push_back(avdeeva::Point{minX, maxY});
    return frame;
  }
  bool isLessPoint(const avdeeva::Point & lhs, const avdeeva::Point & rhs)
  {
    return (lhs.x <= rhs.x) && (lhs.y <= rhs.y);
  }
  bool checkInFrame(const avdeeva::Polygon & polygon, const avdeeva::Polygon & frame)
  {
    avdeeva::Point minPol = minPoint(polygon);
    avdeeva::Point maxPol = maxPoint(polygon);
    avdeeva::Point minFrame = minPoint(frame);
    avdeeva::Point maxFrame = maxPoint(frame);
    bool minPoints = isLessPoint(minFrame, minPol);
    bool maxPoints = isLessPoint(maxPol, maxFrame);
    return minPoints && maxPoints;
  }
}
bool avdeeva::isInFrame(const std::deque< Polygon > & polygons, const Polygon & polygon)
{
  Polygon frame = createFrame(polygons);
  return checkInFrame(polygon, frame);
}
