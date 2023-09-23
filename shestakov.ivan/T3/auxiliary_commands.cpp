#include "auxiliary_commands.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <limits>

namespace shestakov
{
  void printError(std::ostream &out)
  {
    out << "<INVALID COMMAND>\n";
  }
  void skipUntilNewLine(std::istream &in)
  {
    if (!in.eof())
    {
      in.clear();
      auto maxstream = std::numeric_limits<std::streamsize>::max();
      in.ignore(maxstream, '\n');
    }
  }
  bool isEven(const Polygon &polygon)
  {
    return !(polygon.points.size() % 2);
  }
  bool isOdd(const Polygon &polygon)
  {
    return (polygon.points.size() % 2);
  }
  size_t countVertexes(const Polygon &polygon)
  {
    return polygon.points.size();
  }
  bool equalVert(const Polygon &polygon, const size_t vert)
  {
    return polygon.points.size() == vert;
  }
  int getDeterminant(const Point &first, const Point &second)
  {
    int determinant = first.x * second.y - second.x * first.y;
    return determinant;
  }
  std::ostream& printFix(const double src, std::ostream &out)
  {
    return out << std::fixed << std::setprecision(1) << src << '\n';
  }
  double getArea(const Polygon &polygon)
  {
    double area = 0.0;
    std::vector< int > deter(polygon.points.size());
    std::transform(polygon.points.begin(), --polygon.points.end(), ++polygon.points.begin(), deter.begin(), getDeterminant);
    area = std::accumulate(deter.begin(), deter.end(), 0.0);
    area += getDeterminant(polygon.points.back(), polygon.points.front());
    area = std::abs(area) / 2.0;
    return area;
  }
  bool compPoints(const Point& point_1, const Point& point_2)
  {
    return point_1.x == point_2.x && point_1.y == point_2.y;
  }
  bool compTwoPolygons(const Polygon& polygon_1, const Polygon& polygon_2)
  {
    if (polygon_1.points.size() != polygon_2.points.size())
    {
      return false;
    }
    std::vector< bool > coincidence(polygon_1.points.size());
    std::vector< Point > two_polygons(polygon_1.points.size());
    std::copy(polygon_1.points.begin(), polygon_1.points.end(), two_polygons.begin());
    std::copy(polygon_2.points.begin(), polygon_2.points.end(), std::back_inserter(two_polygons));
    std::transform(two_polygons.begin(), two_polygons.end(), two_polygons.begin() + polygon_1.points.size(), coincidence.begin(), compPoints);
    size_t sum = std::accumulate(coincidence.begin(), coincidence.end(), 0);
    return sum == polygon_1.points.size();
  }
  bool compThreePolygons(const Polygon& polygon_1, const Polygon& polygon_2, const Polygon& polygon_3)
  {
    return compTwoPolygons(polygon_1, polygon_2) && compTwoPolygons(polygon_1, polygon_3);
  }
}
