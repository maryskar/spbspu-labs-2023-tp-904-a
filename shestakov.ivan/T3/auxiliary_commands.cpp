#include "auxiliary_commands.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <limits>
#include <iofmtguard.h>

namespace shestakov
{
  void printError(std::ostream& out)
  {
    out << "<INVALID COMMAND>";
  }
  void skipUntilNewLine(std::istream& in)
  {
    if (!in.eof())
    {
      in.clear();
      auto maxstream = std::numeric_limits< std::streamsize >::max();
      in.ignore(maxstream, '\n');
    }
  }
  bool isEven(const Polygon& polygon)
  {
    return !(polygon.points.size() % 2);
  }
  bool isOdd(const Polygon& polygon)
  {
    return (polygon.points.size() % 2);
  }
  size_t countVertexes(const Polygon& polygon)
  {
    return polygon.points.size();
  }
  bool equalVert(const Polygon& polygon, size_t vert)
  {
    return polygon.points.size() == vert;
  }
  int getDeter(const Point& first, const Point& second)
  {
    int determinant = first.x * second.y - second.x * first.y;
    return determinant;
  }
  std::ostream& printFix(double src, std::ostream& out)
  {
    iofmtguard iofmtguard(out);
    return out << std::fixed << std::setprecision(1) << src << '\n';
  }
  double getArea(const Polygon& polygon)
  {
    double area = 0.0;
    std::vector< int > deter(polygon.points.size());
    std::transform(polygon.points.begin(), --polygon.points.end(), ++polygon.points.begin(), deter.begin(), getDeter);
    area = std::accumulate(deter.begin(), deter.end(), 0.0);
    area += getDeter(polygon.points.back(), polygon.points.front());
    area = std::abs(area) / 2.0;
    return area;
  }
  bool compTwoPolygons(const Polygon& polygon_1, const Polygon& polygon_2)
  {
    if (polygon_1.points.size() != polygon_2.points.size())
    {
      return false;
    }
    return polygon_1 == polygon_2;
  }
  bool compThreePolygons(const Polygon& polygon_1, const Polygon& polygon_2, const Polygon& polygon_3)
  {
    return compTwoPolygons(polygon_1, polygon_2) && compTwoPolygons(polygon_1, polygon_3);
  }
}
