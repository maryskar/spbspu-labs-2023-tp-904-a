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
  struct function
  {
    std::function< double(const std::vector< Polygon >&, size_t) > type_1;
    std::function< double(const std::vector< Polygon >&) > type_2;
  };

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
    if (data.empty())
    {
      return 0.0;
    }
    std::vector< double > areas;
    std::transform(data.begin(), data.end(), std::back_inserter(areas), getPolygonArea);
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

  double getMaxArea(const std::vector< Polygon >& data)
  {
    std::vector< double > areas;
    std::transform(data.begin(), data.end(), std::back_inserter(areas), getPolygonArea);
    return *std::max_element(areas.begin(), areas.end());
  }

  double getMaxVerts(const std::vector< Polygon >& data)
  {
    std::vector< size_t > verts;
    std::transform(data.begin(), data.end(), std::back_inserter(verts), getNumOfVerts);
    return *std::max_element(verts.begin(), verts.end());
  }

  class Commands
  {
  public:
   Commands():
     names(),
     type_1(),
     type_2()
   {
     names = {"AREA", "MAX", "MIN", "COUNT", "INFRAME", "RIGHTSHAPES"};

     type_1.insert(std::make_pair("AREA", &getAreaWithEqualNumVerts));
     //type_1.insert(std::make_pair("COUNT", &getAreaWithEqualNumVerts));

     type_2.insert(std::make_pair("EVEN", &getAreaEven));
     type_2.insert(std::make_pair("ODD", &getAreaOdd));
     type_2.insert(std::make_pair("MEAN", &getAreaMean));
     type_2.insert(std::make_pair("AREA", &getMaxArea));
     type_2.insert(std::make_pair("VERTEXES", &getMaxVerts));
   }

   bool find(const std::string& name)
   {
     return std::find(names.begin(), names.end(), name) != names.end();
   }

   void get(const std::string& key, std::function< double(const std::vector< Polygon >&, const size_t&) >& command)
   {
     try
     {
       command = type_1.at(key);
     }
     catch (const std::out_of_range&)
     {
       throw std::out_of_range("Not found");
     }
   }

   void get(const std::string& key, std::function< double(const std::vector< Polygon >&) >& command)
   {
     try
     {
       command = type_2.at(key);
     }
     catch (const std::out_of_range&)
     {
       throw std::out_of_range("Not found");
     }
   }

  private:
   std::vector< std::string > names;
   std::map< std::string, std::function< double(const std::vector< Polygon >&, const size_t&) > > type_1;
   std::map< std::string, std::function< double(const std::vector< Polygon >&) > > type_2;
  };
}
#endif
