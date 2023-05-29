#ifndef COMMANDS_H
#define COMMANDS_H

#include <cstddef>
#include <map>
#include <functional>
#include <algorithm>
#include <numeric>

#include "data_struct.h"

namespace tarasenko
{
  using namespace std::placeholders;

  size_t getNumOfVerts(const Polygon& p)
  {
    return p.points.size();
  }

  double getTriangleArea(const Point& a, const Point& b, const Point& c)
  {
    double m = a.x * b.y + b.x * c.y + c.x * a.y;
    double n = b.x * a.y + c.x * b.y + a.x * c.y;
    double s = (m - n) / 2.0;
    return std::abs(s);
  }

  double getPolygonArea(const Polygon& polygon)
  {
    if (polygon.points.size() < 3)
    {
      return 0.0;
    }
    Point first = polygon.points[0];
    std::vector< double > areas;
    auto calculateAreas = std::bind(getTriangleArea, first, _1, _2);

    std::transform(polygon.points.begin() + 1, polygon.points.end() - 1,
                   polygon.points.begin() + 2,
                   std::back_inserter(areas), calculateAreas);

    double area = std::accumulate(areas.begin(), areas.end(), 0.0);
    return area;
  }

  double getAreaEven(const std::vector< Polygon >& data)
  {
    auto result = 0.0;
    for (size_t i = 0; i < data.size(); ++i)
    {
      if (getNumOfVerts(data[i]) % 2)
      {
        result += getPolygonArea(data[i]);
      }
    }
    return result;
  }

  double getAreaOdd(const std::vector< Polygon >& data)
  {
    auto result = 0.0;

    for (size_t i = 0; i < data.size(); ++i)
    {
      if (!(getNumOfVerts(data[i]) % 2))
      {
        result += getPolygonArea(data[i]);
      }
    }
    return result;
  }

  class Commands
  {
  public:
   Commands():
     type_calc()
   {
     type_calc.insert(std::make_pair("EVEN", &getAreaEven));
     type_calc.insert(std::make_pair("ODD", &getAreaOdd));
   }

   bool findInTypeCalc(std::string command)
   {
     return type_calc.find(command) != type_calc.cend();
   }

   std::function< double(const std::vector< Polygon >&) >& calc(const std::string& key)
   {
     return type_calc.at(key);
   }

  private:
   std::map< std::string, std::function< double(const std::vector< Polygon >&) > > type_calc;
  };

}
#endif
