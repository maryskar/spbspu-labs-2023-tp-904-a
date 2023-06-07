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
