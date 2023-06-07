#include "commands.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <functional>
#include "polygon.h"
#include "io.h"
namespace
{
  typedef dimkashelk::Polygon polygon;
  typedef std::vector< polygon > v_polygon;
  using pair = std::pair< double, double >;
  using point = dimkashelk::Point;
  bool isMultiple(const polygon &pol, size_t number)
  {
    if (number == 0)
    {
      throw std::logic_error("Division by zero");
    }
    return pol.points.size() % number == 0;
  }
  bool isEven(const polygon &pol)
  {
    return isMultiple(pol, 2);
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
  template< typename UnaryOperation >
  v_polygon getFilteredPolygons(const v_polygon &pol, UnaryOperation op)
  {
    v_polygon result;
    std::copy_if(pol.begin(), pol.end(), std::back_inserter(result), op);
    return result;
  }
  template< typename UnaryOperation >
  void printArea(const v_polygon &pol, std::ostream &out, UnaryOperation op)
  {
    auto filtered = getFilteredPolygons(pol, op);
    std::vector< double > filtered_area;
    std::transform(filtered.begin(), filtered.end(), std::back_inserter(filtered_area), dimkashelk::getArea);
    dimkashelk::iofmtguard iofmtguard(out);
    out << std::setprecision(1) << std::accumulate(filtered_area.begin(), filtered_area.end(), 0.0);
  }
  template< typename UnaryOperation >
  void printResult(const v_polygon &pol, std::ostream &out, UnaryOperation op)
  {
    auto res = *std::max_element(pol.begin(), pol.end(), op);
    out << std::setprecision(1) << getArea(res);
  }
  template< typename UnaryOperation >
  void printCount(const v_polygon &pol, std::ostream &out, UnaryOperation op)
  {
    auto res = std::count_if(pol.begin(), pol.end(), op);
    out << res;
  }
  unsigned getDirection(const point f, const point s, const point t)
  {
    int res = (s.y - f.y) * (t.x - s.x) - (s.x - f.x) * (t.y - s.y);
    return (res < 0)? -1: (res > 0)? 1: 0;
  }
  bool isIntersectTwoSegment(const point first1, const point first2, const point second1, const point second2)
  {
    unsigned res11 = getDirection(first1, first2, second1);
    unsigned res12 = getDirection(first1, first2, second2);
    unsigned res21 = getDirection(second1, second2, first1);
    unsigned res22 = getDirection(second1, second2, first2);
    return res11 != res12 && res21 != res22;
  }
  pair getIntersectTwoSegment(const pair first, const pair second)
  {
    return {std::min(first.first, second.first), std::max(first.second, second.second)};
  }
  pair getProjectionOnX(const dimkashelk::Point &first, const dimkashelk::Point &second)
  {
    return {first.x, second.x};
  }
  pair getProjectionOnXOfPolygon(const polygon &pol)
  {
    std::vector< pair > values;
    auto begin_first = pol.points.begin();
    auto begin_second = begin_first;
    begin_second++;
    auto end = pol.points.end();
    end--;
    std::transform(begin_first, end, begin_second, std::back_inserter(values), getProjectionOnX);
    auto res = std::accumulate(values.begin(), values.end(), std::pair< double, double >{0.0, 0.0}, getIntersectTwoSegment);
    return res;
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
  std::vector< double > areas;
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
  auto checker = std::bind(isMultiple, _1, num);
  printArea(pol, out, checker);
}
void dimkashelk::printMaxArea(const std::vector< Polygon > &pol, std::ostream &out)
{
  printResult(pol, out, isLessArea);
}
void dimkashelk::printMaxVertex(const std::vector< Polygon > &pol, std::ostream &out)
{
  printResult(pol, out, isLessVertex);
}
void dimkashelk::printMinArea(const std::vector< Polygon > &pol, std::ostream &out)
{
  using namespace std::placeholders;
  printResult(pol, out, std::bind(isLessArea, _2, _1));
}
void dimkashelk::printMinVertex(const std::vector< Polygon > &pol, std::ostream &out)
{
  using namespace std::placeholders;
  printResult(pol, out, std::bind(isLessVertex, _2, _1));
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
  using namespace std::placeholders;
  printCount(pol, out, std::bind(isEqualNum, _1, num));
}
