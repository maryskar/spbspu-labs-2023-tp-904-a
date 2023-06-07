#ifndef FUNCS_FOR_COMMANDS_H
#define FUNCS_FOR_COMMANDS_H

#include <cstddef>
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

  size_t getMaxVerts(const std::vector< Polygon >& data)
  {
    std::vector< size_t > verts;
    std::transform(data.begin(), data.end(), std::back_inserter(verts), getNumOfVerts);
    return *std::max_element(verts.begin(), verts.end());
  }

  double getMinArea(const std::vector< Polygon >& data)
  {
    std::vector< double > areas;
    std::transform(data.begin(), data.end(), std::back_inserter(areas), getPolygonArea);
    return *std::min_element(areas.begin(), areas.end());
  }

  size_t getMinVerts(const std::vector< Polygon >& data)
  {
    std::vector< size_t > verts;
    std::transform(data.begin(), data.end(), std::back_inserter(verts), getNumOfVerts);
    return *std::min_element(verts.begin(), verts.end());
  }

  size_t getNumEven(const std::vector< Polygon >& data)
  {
    auto cond = std::bind(isEven, std::bind(getNumOfVerts, _1));
    return std::count_if(data.begin(), data.end(), cond);
  }

  size_t getNumOdd(const std::vector< Polygon >& data)
  {
    auto cond = std::bind(isOdd, std::bind(getNumOfVerts, _1));
    return std::count_if(data.begin(), data.end(), cond);
  }

  size_t getNumWithEqualNumVerts(const std::vector< Polygon >& data, size_t n)
  {
    auto cond = std::bind(std::equal_to< size_t >{}, std::bind(getNumOfVerts, _1), n);
    return std::count_if(data.begin(), data.end(), cond);
  }

  bool isRightAngle(const Point& a, const Point& b, const Point& c)
  {
    return (b.x - a.x) * (c.x - b.x) + (b.y - a.y) * (c.y - b.y) == 0;
  }

  bool hasRightAngles(const Polygon& p)
  {
    auto n = p.points.size();
    for (int i = 0; i < n; i++)
    {
      Point a = p.points[i];
      Point b = p.points[(i + 1) % n];
      Point c = p.points[(i + 2) % n];
      if (isRightAngle(a, b, c))
      {
        return true;
      }
    }
    return false;
  }

  size_t getNumRightShapes(const std::vector< Polygon >& data)
  {
    return std::count_if(data.begin(), data.end(), hasRightAngles);
  }
}
#endif
