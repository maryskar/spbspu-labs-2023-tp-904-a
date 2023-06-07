#include "commands.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include "polygon.h"
#include "io.h"
namespace
{
  typedef dimkashelk::Polygon polygon;
  bool isEven(const polygon &polygon)
  {
    return polygon.points.size() % 2 == 0;
  }
  void printArea(const std::vector< polygon > &filtered, std::ostream &out)
  {
    std::vector< double > filtered_area;
    std::transform(filtered.begin(), filtered.end(), std::back_inserter(filtered_area), dimkashelk::getArea);
    dimkashelk::iofmtguard iofmtguard(out);
    out << std::setprecision(1) << std::accumulate(filtered_area.begin(), filtered_area.end(), 0.0);
  }
}
void dimkashelk::printAreaEven(const std::vector< Polygon > &polygon, std::ostream &out)
{

}
