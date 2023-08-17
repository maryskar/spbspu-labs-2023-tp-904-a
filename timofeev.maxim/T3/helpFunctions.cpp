#include "helpFunctions.h"
#include <ostream>
#include <vector>
#include <cmath>
#include "polygon.h"
namespace timofeev
{
  bool is_number(const std::string& s)
  {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
  }
  void printError(std::ostream& out)
  {
    out << "<INVALID COMMAND>" << "\n";
  }

  bool isOdd(const Polygon& polygon)
  {
    return polygon.points.size() % 2;
  }

  bool isEven(const Polygon& polygon)
  {
    return !(isOdd(polygon));
  }


  double getArea(const std::vector<Polygon> &pol)
  {
    /*
     * (0 0)
     * (0 2)  0*2+0*2+2*0+0*0
     * (2 2)  0*0+2*2+2*2+2*0
     * (2 0)
     */
    double totalArea = 0.0;
    for (auto it = pol.begin(); it != pol.end(); ++it)
    {
      const Polygon &p = *it;
      const std::vector<Point> &points = p.points;
      double area = 0.0;
      double firstSum = 0.0;
      double secondSum = 0.0;
      for (size_t i = 0; i < points.size(); i++)
      {
        const Point &point1 = points[i];
        const Point &point2 = points[(i + 1) % points.size()];
        firstSum += (static_cast< double >(point1.x * point2.y));
        secondSum += (static_cast< double >(point1.y * point2.x));
      }
      area += firstSum - secondSum;
      totalArea += area;
    }
    return std::abs(totalArea) / 2.0;
  }

  void doEven(const std::vector< Polygon >& res)
  {

  }
  void doOdd(const std::vector< Polygon >& res);
  void doMaxArea(const std::vector< Polygon >& res);
  void doMaxV(const std::vector< Polygon >& res);
  void doMinArea(const std::vector< Polygon >& res);
  void doMinV(const std::vector< Polygon >& res);
  void doСountEven(const std::vector< Polygon >& res);
  void doCountOdd(const std::vector< Polygon >& res);


}