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
  bool isEven(const polygon &polygon)
  {
    return polygon.points.size() % 2 == 0;
  }
  void printArea(const v_polygon &filtered, std::ostream &out)
  {
    std::vector< double > filtered_area;
    std::transform(filtered.begin(), filtered.end(), std::back_inserter(filtered_area), dimkashelk::getArea);
    dimkashelk::iofmtguard iofmtguard(out);
    out << std::setprecision(1) << std::accumulate(filtered_area.begin(), filtered_area.end(), 0.0);
  }
  template< typename UnaryOperation >
  v_polygon getFilteredPolygons(const v_polygon &pol, UnaryOperation op)
  {
    v_polygon result;
    std::copy_if(pol.begin(), pol.end(), std::back_inserter(result), op);
    return result;
  }
}
void dimkashelk::printAreaEven(const std::vector< Polygon > &polygon, std::ostream &out)
{
  auto filtered = getFilteredPolygons(polygon, isEven);
  printArea(filtered, out);
}
