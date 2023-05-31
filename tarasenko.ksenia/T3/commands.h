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

  bool isEven(size_t n)
  {
    return !(n % 2);
  }

  bool isOdd(size_t n)
  {
    return !isEven(n);
  }

  double getAreaEven(const std::vector< Polygon >& data)
  {
    auto cond = std::bind(isEven, std::bind(getNumOfVerts, _1));
    auto evenPolygons = std::vector< Polygon >{};
    std::copy_if(data.begin(), data.end(), std::back_inserter(evenPolygons), cond);
    std::vector< double > areas;
    std::transform(evenPolygons.begin(), evenPolygons.end(),
                   std::back_inserter(areas), getPolygonArea);
    return std::accumulate(areas.begin(), areas.end(), 0.0);
  }

  double getAreaOdd(const std::vector< Polygon >& data)
  {
    auto cond = std::bind(isOdd, std::bind(getNumOfVerts, _1));
    auto oddPolygons = std::vector< Polygon >{};
    std::copy_if(data.begin(), data.end(), std::back_inserter(oddPolygons), cond);
    std::vector< double > areas;
    std::transform(oddPolygons.begin(), oddPolygons.end(),
                   std::back_inserter(areas), getPolygonArea);
    return std::accumulate(areas.begin(), areas.end(), 0.0);
  }

  double getAreaMean(const std::vector< Polygon >& data)
  {
    std::vector< double > areas;
    std::transform(data.begin(), data.end(), std::back_inserter(areas), getPolygonArea);
    if (!data.size())
    {
      return 0.0;
    }
    return std::accumulate(areas.begin(), areas.end(), 0.0) / data.size();
  }

  double getAreaWithEqualNumVerts(const std::vector< Polygon >& data, size_t n)
  {
    auto cond = std::bind(std::equal_to< size_t >{}, std::bind(getNumOfVerts, _1), n);
    auto equalPolygons = std::vector< Polygon >{};
    std::copy_if(data.begin(), data.end(), std::back_inserter(equalPolygons), cond);
    std::vector< double > areas;
    std::transform(equalPolygons.begin(), equalPolygons.end(),
                   std::back_inserter(areas), getPolygonArea);
    return std::accumulate(areas.begin(), areas.end(), 0.0);
  }

  class Commands
  {
  public:
   Commands():
     type_calc1(),
     type_calc2()
   {
     type_calc1.insert(std::make_pair("AREA", &getAreaWithEqualNumVerts));

     type_calc2.insert(std::make_pair("EVEN", &getAreaEven));
     type_calc2.insert(std::make_pair("ODD", &getAreaOdd));
     type_calc2.insert(std::make_pair("MEAN", &getAreaMean));
   }
   bool findInTypeCalc1(std::string command)
   {
     return type_calc1.find(command) != type_calc1.cend();
   }

   bool findInTypeCalc2(std::string command)
   {
     return type_calc2.find(command) != type_calc2.cend();
   }

   std::function< double(const std::vector< Polygon >&, size_t) >& calc1(const std::string& key)
   {
     return type_calc1.at(key);
   }

   std::function< double(const std::vector< Polygon >&) >& calc2(const std::string& key)
   {
     return type_calc2.at(key);
   }

  private:
   std::map< std::string, std::function< double(const std::vector< Polygon >&, size_t) > > type_calc1;
   std::map< std::string, std::function< double(const std::vector< Polygon >&) > > type_calc2;
  };
}
#endif
