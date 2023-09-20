#include "commands.h"
#include <iomanip>
#include "extra_commands.h"

namespace mishanina{
  void printAreaEven(const std::vector<Polygon>& polygons, std::ostream& out){
    out << std::fixed << std::setprecision(1) << getAreaIf(polygons, isEven) << '\n';
  }
  void printAreaOdd(const std::vector<Polygon>& polygons, std::ostream& out){
    out << std::fixed << std::setprecision(1) << getAreaIf(polygons, isOdd) << '\n';
  }
  void printAreaMean(const std::vector<Polygon>& polygons, std::ostream& out){
    if (polygons.empty())
    {
      throw std::invalid_argument("ERROR : polygons are empty");
    }
    out << std::fixed << std::setprecision(1) << getTotalArea(polygons) / polygons.size() << '\n';
  }
}