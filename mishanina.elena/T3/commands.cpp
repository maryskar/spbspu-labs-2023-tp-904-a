#include "commands.h"
#include <iomanip>
#include "extra_commands.h"
namespace mishanina
{
  void printAreaEven(const std::vector<Polygon> &polygons, std::ostream &out)
  {
    out << std::fixed << std::setprecision(1) << getAreaIf(polygons, isEven) << '\n';
  }
  void printAreaOdd(const std::vector<Polygon> &polygons, std::ostream &out)
  {
    out << std::fixed << std::setprecision(1) << getAreaIf(polygons, isOdd) << '\n';
  }
  void printAreaMean(const std::vector<Polygon> &polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("ERROR : polygons are empty");
    }
    out << std::fixed << std::setprecision(1) << getTotalArea(polygons) / polygons.size() << '\n';
  }
  void printAreaNumOfVertexes(const std::vector<Polygon> &polygons, std::ostream &out, std::size_t num)
  {
    if (num < 3)
    {
      throw std::invalid_argument("ERROR : invalid parameter");
    }
    std::vector<Polygon> polygonsNum = getPolygonsWithNumOfVertexes(polygons, num);
    out << std::fixed << std::setprecision(1) << getTotalArea(polygonsNum) << '\n';
  }
  void printMaxArea(const std::vector<Polygon> &polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("ERROR : polygons are empty");
    }
    out << std::fixed << std::setprecision(1) << getMaxMinArea(polygons, true) << '\n';
  }
  void printMaxVertexes(const std::vector<Polygon> &polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("ERROR : polygons are empty");
    }
    out << getMaxMinVert(polygons, true) << '\n';
  }
  void printMinArea(const std::vector<Polygon> &polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("ERROR : polygons are empty");
    }
    out << std::fixed << std::setprecision(1) << getMaxMinArea(polygons, false) << '\n';
  }
  void printMinVertexes(const std::vector<Polygon> &polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("ERROR : polygons are empty");
    }
    out << getMaxMinVert(polygons, false) << '\n';
  }
  void printCountEven(const std::vector<Polygon> &polygons, std::ostream &out)
  {
    out << getCountIf(polygons, isEven) << '\n';
  }
  void printCountOdd(const std::vector<Polygon> &polygons, std::ostream &out)
  {
    out << getCountIf(polygons, isOdd) << '\n';
  }
  void printCountNumOfVertexes(const std::vector<Polygon> &polygons, std::ostream &out, std::size_t num)
  {
    if (num < 3)
    {
      throw std::invalid_argument("ERROR : invalid parameter");
    }
    std::vector<Polygon> polNum = getPolygonsWithNumOfVertexes(polygons, num);
    out << polNum.size() << '\n';
  }
  void printRects(const std::vector<Polygon>& polygons, std::ostream& out)
  {
    out << getCountIf(polygons, isRectangle) << '\n';
  }
}