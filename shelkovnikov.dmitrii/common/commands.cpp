#include "commands.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include "polygon.h"
#include "io.h"
namespace
{
  typedef dimkashelk::Polygon polygon;
  typedef std::vector< polygon > v_polygon;
  bool isMultiple(const polygon &pol, int number)
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
    out << std::setprecision(1) << std::accumulate(filtered_area.begin(), filtered_area.end(), 0.0) << '\n';
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
  out << std::fixed << std::setprecision(1) << (sum_area / pol.size()) << '\n';
}
