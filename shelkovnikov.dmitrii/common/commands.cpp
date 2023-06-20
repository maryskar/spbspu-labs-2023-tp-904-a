#include "commands.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <tuple>
#include <functional>
#include "polygon.h"
#include "io.h"
namespace
{
  using polygon = dimkashelk::Polygon;
  using v_polygon = std::vector< polygon >;
  using point = dimkashelk::Point;
  bool isEven(const polygon &pol)
  {
    using size_type = std::vector< point >::size_type;
    using namespace std::placeholders;
    auto res = std::bind(std::equal_to< size_type >{}, std::bind(std::modulus< size_type >{}, _1, 2), 0);
    return res(pol.points.size());
  }
  bool isOdd(const polygon &pol)
  {
    return !isEven(pol);
  }
  bool isLessArea(const polygon &lnr, const polygon &rnl)
  {
    return dimkashelk::getArea(lnr) < dimkashelk::getArea(rnl);
  }
  bool isEqualNum(const polygon &pol, size_t num)
  {
    return pol.points.size() == num;
  }
  bool isLessVertex(const polygon &lnr, const polygon &rnl)
  {
    return lnr.points.size() < rnl.points.size();
  }
  template < typename UnaryOperation >
  v_polygon getFilteredPolygons(const v_polygon &pol, UnaryOperation op)
  {
    v_polygon result;
    std::copy_if(pol.begin(), pol.end(), std::back_inserter(result), op);
    return result;
  }
  template < typename UnaryOperation >
  void printArea(const v_polygon &pol, std::ostream &out, UnaryOperation op)
  {
    auto filtered = getFilteredPolygons(pol, op);
    std::vector< double > filtered_area(filtered.size());
    std::transform(filtered.begin(), filtered.end(), std::back_inserter(filtered_area), dimkashelk::getArea);
    dimkashelk::iofmtguard iofmtguard(out);
    out << std::fixed <<std::setprecision(1) << std::accumulate(filtered_area.begin(), filtered_area.end(), 0.0);
  }
  template < typename UnaryOperation >
  polygon getResult(const v_polygon &pol, UnaryOperation op)
  {
    if (pol.empty())
    {
      throw std::logic_error("Nothing...");
    }
    return *std::max_element(pol.begin(), pol.end(), op);
  }
  template < typename UnaryOperation >
  void printResult(const v_polygon &pol, std::ostream &out, UnaryOperation op)
  {
    auto res = getResult(pol, op);
    dimkashelk::iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getArea(res);
  }
  template < typename UnaryOperation >
  void printResultVertex(const v_polygon &pol, std::ostream &out, UnaryOperation op)
  {
    auto res = getResult(pol, op);
    dimkashelk::iofmtguard iofmtguard(out);
    out << res.points.size();
  }
  template < typename UnaryOperation >
  void printCount(const v_polygon &pol, std::ostream &out, UnaryOperation op)
  {
    auto res = std::count_if(pol.begin(), pol.end(), op);
    dimkashelk::iofmtguard iofmtguard(out);
    out << res;
  }
  unsigned getDirection(const point f, const point s, const point t)
  {
    int res = (s.y - f.y) * (t.x - s.x) - (s.x - f.x) * (t.y - s.y);
    return (res < 0) ? -1 : (res > 0) ? 1 : 0;
  }
  bool isIntersectTwoSegment(const point first1, const point first2, const point second1, const point second2)
  {
    unsigned res11 = getDirection(first1, first2, second1);
    unsigned res12 = getDirection(first1, first2, second2);
    unsigned res21 = getDirection(second1, second2, first1);
    unsigned res22 = getDirection(second1, second2, first2);
    return (res11 != res12 && res21 != res22) || res11 == 0 || res12 == 0 || res21 == 0 || res22 == 0;
  }
  bool isPointInPolygon(const polygon &pol, const point p)
  {
    using namespace std::placeholders;
    auto func = std::bind(getDirection, _1, _2, p);
    std::vector< unsigned > values(pol.points.size());
    std::transform(pol.points.begin(), --pol.points.end(), ++pol.points.begin(), std::back_inserter(values), func);
    values.push_back(func(*(--pol.points.end()), *pol.points.begin()));
    auto res = static_cast< long long >(std::accumulate(values.begin(), values.end(), 0));
    auto long_long_size = static_cast< long long >(values.size());
    return res == long_long_size;
  }
  bool isPolygonInPolygon(const polygon &first, const polygon &second)
  {
    using namespace std::placeholders;
    auto func = std::bind(isPointInPolygon, first, _1);
    std::vector< bool > values(second.points.size());
    std::transform(second.points.begin(), second.points.end(), std::back_inserter(values), func);
    auto res = std::find(values.begin(), values.end(), false);
    return res == values.end();
  }
  template < typename BinaryOperation >
  bool isIntersect(BinaryOperation func, const polygon &pol)
  {
    std::vector< bool > values(pol.points.size());
    auto begin_first = pol.points.begin();
    auto begin_second = begin_first;
    begin_second++;
    auto end = pol.points.end();
    end--;
    std::transform(begin_first, end, begin_second, std::back_inserter(values), func);
    values.push_back(func(pol.points.front(), pol.points.back()));
    auto res = std::count(values.begin(), values.end(), true);
    return res > 0;
  }
  bool isIntersectSegmentAndPolygon(const polygon &pol, const point first1, const point first2)
  {
    using namespace std::placeholders;
    auto func = std::bind(isIntersectTwoSegment, _1, _2, first1, first2);
    return isIntersect(func, pol);
  }
  bool isIntersectTwoPolygon(const polygon &first, const polygon &second)
  {
    using namespace std::placeholders;
    auto func = std::bind(isIntersectSegmentAndPolygon, second, _1, _2);
    return isIntersect(func, first) || isPolygonInPolygon(first, second);
  }
  bool isEqualPoint(const point &p1, const point &p2)
  {
    return p1.x == p2.x && p1.y == p2.y;
  }
  point movePoint(const point &p, int dX, int dY)
  {
    return {p.x - dX, p.y - dY};
  }
  polygon moveFirstCoordToStartCoords(const polygon &pol)
  {
    int diffX = pol.points.front().x;
    int diffY = pol.points.front().y;
    using namespace std::placeholders;
    auto func = std::bind(movePoint, _1, diffX, diffY);
    std::vector< point > newPoints(pol.points.size());
    std::transform(pol.points.begin(), pol.points.end(), std::back_inserter(newPoints), func);
    return polygon{newPoints};
  }
  bool isSamePolygons(const polygon &first, const polygon &second)
  {
    if (first.points.size() != second.points.size())
    {
      return false;
    }
    auto movedFirst = moveFirstCoordToStartCoords(first);
    auto movedSecond = moveFirstCoordToStartCoords(second);
    return std::equal(movedFirst.points.begin(), movedFirst.points.end(), movedSecond.points.begin(), isEqualPoint);
  }
}
void dimkashelk::printAreaEven(const std::vector< Polygon > &pol, std::ostream &out)
{
  printArea(pol, out, isEven);
}
void dimkashelk::printAreaOdd(const std::vector< Polygon > &pol, std::ostream &out)
{
  printArea(pol, out, isOdd);
}
void dimkashelk::printAreaMean(const std::vector< Polygon > &pol, std::ostream &out)
{
  if (pol.empty())
  {
    throw std::logic_error("No mean area of empty vector");
  }
  std::vector< double > areas(pol.size());
  std::transform(pol.begin(), pol.end(), std::back_inserter(areas), getArea);
  double sum_area = std::accumulate(areas.begin(), areas.end(), 0.0);
  iofmtguard iofmtguard(out);
  out << std::fixed << std::setprecision(1) << (sum_area / pol.size());
}
void dimkashelk::printAreaNumOfVertex(const std::vector< Polygon > &pol, std::ostream &out, size_t num)
{
  if (num < 3)
  {
    throw std::logic_error("No polygons with this count of vertex");
  }
  using namespace std::placeholders;
  auto checker = std::bind(isEqualNum, _1, num);
  printArea(pol, out, checker);
}
void dimkashelk::printMaxArea(const std::vector< Polygon > &pol, std::ostream &out)
{
  printResult(pol, out, isLessArea);
}
void dimkashelk::printMaxVertex(const std::vector< Polygon > &pol, std::ostream &out)
{
  printResultVertex(pol, out, isLessVertex);
}
void dimkashelk::printMinArea(const std::vector< Polygon > &pol, std::ostream &out)
{
  using namespace std::placeholders;
  printResult(pol, out, std::bind(isLessArea, _2, _1));
}
void dimkashelk::printMinVertex(const std::vector< Polygon > &pol, std::ostream &out)
{
  using namespace std::placeholders;
  printResultVertex(pol, out, std::bind(isLessVertex, _2, _1));
}
void dimkashelk::printCountEven(const std::vector< Polygon > &pol, std::ostream &out)
{
  printCount(pol, out, isEven);
}
void dimkashelk::printCountOdd(const std::vector< Polygon > &pol, std::ostream &out)
{
  printCount(pol, out, isOdd);
}
void dimkashelk::printCountNumOfVertex(const std::vector< Polygon > &pol, std::ostream &out, size_t num)
{
  if (num < 3)
  {
    throw std::logic_error("No polygons");
  }
  using namespace std::placeholders;
  auto func = std::bind(isEqualNum, _1, num);
  out << std::count_if(pol.begin(), pol.end(), func);
}
void dimkashelk::printIntersections(const std::vector< Polygon > &pol, std::ostream &out, std::istream &in)
{
  Polygon polygon;
  in >> polygon;
  if (!in)
  {
    throw std::logic_error("Check input");
  }
  std::vector< bool > values(pol.size());
  using namespace std::placeholders;
  auto func = std::bind(isIntersectTwoPolygon, _1, polygon);
  std::transform(pol.begin(), pol.end(), std::back_inserter(values), func);
  auto res = std::count(values.begin(), values.end(), true);
  dimkashelk::iofmtguard iofmtguard(out);
  out << res;
}
void dimkashelk::printSame(const std::vector< Polygon > &pol, std::ostream &out, std::istream &in)
{
  Polygon polygon;
  in >> polygon;
  if (!in)
  {
    throw std::logic_error("Check input");
  }
  using namespace std::placeholders;
  auto filterBySize = std::bind(isEqualNum, _1, polygon.points.size());
  auto filteredBySize = getFilteredPolygons(pol, filterBySize);
  auto func = std::bind(isSamePolygons, _1, polygon);
  auto count = std::count_if(filteredBySize.begin(), filteredBySize.end(), func);
  dimkashelk::iofmtguard iofmtguard(out);
  out << count;
}
