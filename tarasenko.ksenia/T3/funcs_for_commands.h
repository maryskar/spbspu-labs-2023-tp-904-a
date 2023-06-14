#ifndef FUNCS_FOR_COMMANDS_H
#define FUNCS_FOR_COMMANDS_H

#include <cstddef>
#include <functional>
#include <algorithm>
#include <numeric>
#include <valarray>
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

  double getPolygonArea(const Polygon& p)
  {
    if (p.points.size() < 3)
    {
      throw std::invalid_argument("The figure is incorrect");
    }
    Point first = p.points[0];
    std::vector< double > areas = {};
    auto calculateArea = std::bind(getTriangleArea, first, _1, _2);

    std::transform(p.points.begin() + 1, p.points.end() - 1, p.points.begin() + 2,
                   std::back_inserter(areas), calculateArea);

    double area = std::accumulate(areas.begin(), areas.end(), 0.0);
    return area;
  }

  bool hasEvenVerts(const Polygon& p)
  {
    return !(getNumOfVerts(p) % 2);
  }

  bool hasOddVerts(const Polygon& p)
  {
    return !hasEvenVerts(p);
  }

  double getPolygonAreaIf(const Polygon& p, bool(*cond)(const Polygon& p))
  {
    return cond(p) ? getPolygonArea(p) : 0.0;
  }

  double getAreaIf(const std::vector< Polygon >& data, bool(*cond)(const Polygon& p))
  {
    auto op = std::bind(getPolygonAreaIf, _1, cond);
    std::vector< double > areas = {};
    std::transform(data.begin(), data.end(), std::back_inserter(areas), op);
    return std::accumulate(areas.begin(), areas.end(), 0.0);
  }

  double getAreaEven(const std::vector< Polygon >& data)
  {
    return getAreaIf(data, hasEvenVerts);
  }

  double getAreaOdd(const std::vector< Polygon >& data)
  {
    return getAreaIf(data, hasOddVerts);
  }

  double getAreaMean(const std::vector< Polygon >& data)
  {
    if (data.empty())
    {
      throw std::invalid_argument("Data is empty");
    }
    std::vector< double > areas = {};
    std::transform(data.begin(), data.end(), std::back_inserter(areas), getPolygonArea);
    return std::accumulate(areas.begin(), areas.end(), 0.0) / data.size();
  }

  double getAreaWithEqualNumVerts(const std::vector< Polygon >& data, size_t n)
  {
    auto cond = std::bind(std::equal_to< size_t >{}, std::bind(getNumOfVerts, _1), n);
    auto equalPolygons = std::vector< Polygon >{};
    std::copy_if(data.begin(), data.end(), std::back_inserter(equalPolygons), cond);
    std::vector< double > areas = {};
    std::transform(equalPolygons.begin(), equalPolygons.end(),
                   std::back_inserter(areas), getPolygonArea);
    return std::accumulate(areas.begin(), areas.end(), 0.0);
  }

  double getMaxArea(const std::vector< Polygon >& data)
  {
    std::vector< double > areas = {};
    std::transform(data.begin(), data.end(), std::back_inserter(areas), getPolygonArea);
    return *std::max_element(areas.begin(), areas.end());
  }

  size_t getMaxVerts(const std::vector< Polygon >& data)
  {
    std::vector< size_t > verts = {};
    std::transform(data.begin(), data.end(), std::back_inserter(verts), getNumOfVerts);
    return *std::max_element(verts.begin(), verts.end());
  }

  double getMinArea(const std::vector< Polygon >& data)
  {
    std::vector< double > areas = {};
    std::transform(data.begin(), data.end(), std::back_inserter(areas), getPolygonArea);
    return *std::min_element(areas.begin(), areas.end());
  }

  size_t getMinVerts(const std::vector< Polygon >& data)
  {
    std::vector< size_t > verts = {};
    std::transform(data.begin(), data.end(), std::back_inserter(verts), getNumOfVerts);
    return *std::min_element(verts.begin(), verts.end());
  }

  size_t getNumEven(const std::vector< Polygon >& data)
  {
    return std::count_if(data.begin(), data.end(), hasEvenVerts);
  }

  size_t getNumOdd(const std::vector< Polygon >& data)
  {
    return std::count_if(data.begin(), data.end(), hasOddVerts);
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
    auto points = p.points;
    auto cond = [&](size_t i){
      Point a = points[i];
      Point b = points[(i + 1) % n];
      Point c = points[(i + 2) % n];
      return isRightAngle(a, b, c);
    };
    std::vector< size_t > indexes(n);
    std::iota(indexes.begin(), indexes.end(), 0);
    return std::any_of(indexes.begin(), indexes.end(), cond);
  }

  size_t getNumRightShapes(const std::vector< Polygon >& data)
  {
    return std::count_if(data.begin(), data.end(), hasRightAngles);
  }

  int getX(const Point& point)
  {
    return point.x;
  }

  int getY(const Point& point)
  {
    return point.y;
  }

  Polygon getFrameRect(const Polygon& p)
  {
    std::vector< int > v_x;
    std::vector< int > v_y;
    std::transform(p.points.begin(), p.points.end(), std::back_inserter(v_x), getX);
    std::transform(p.points.begin(), p.points.end(), std::back_inserter(v_y), getY);
    int min_x = *std::min_element(v_x.begin(), v_x.end());
    int min_y = *std::min_element(v_y.begin(), v_y.end());
    int max_x = *std::max_element(v_x.begin(), v_x.end());
    int max_y = *std::max_element(v_y.begin(), v_y.end());

    std::vector< Point > points_rect{{min_x, min_y}, {min_x, max_y},
       {max_x, max_y}, {max_x, min_y}};
    return Polygon{points_rect};
  }

  int getMinX(const Polygon& p)
  {
    std::vector< int > v_x;
    std::transform(p.points.begin(), p.points.end(), std::back_inserter(v_x), getX);
    return *std::min_element(v_x.begin(), v_x.end());
  }

  int getMinY(const Polygon& p)
  {
    std::vector< int > v_y;
    std::transform(p.points.begin(), p.points.end(), std::back_inserter(v_y), getY);
    return *std::min_element(v_y.begin(), v_y.end());
  }

  int getMaxX(const Polygon& p)
  {
    std::vector< int > v_x;
    std::transform(p.points.begin(), p.points.end(), std::back_inserter(v_x), getX);
    return *std::max_element(v_x.begin(), v_x.end());
  }

  int getMaxY(const Polygon& p)
  {
    std::vector< int > v_y;
    std::transform(p.points.begin(), p.points.end(), std::back_inserter(v_y), getY);
    return *std::max_element(v_y.begin(), v_y.end());
  }

  Polygon getFrameRectForCompositeShapes(const std::vector< Polygon >& data)
  {
    if (data.empty())
    {
      throw std::invalid_argument("Data is empty");
    }
    auto comp_minx = std::bind(std::less<>{}, std::bind(getMinX, _1), std::bind(getMinX, _2));
    auto poly_with_minx = std::min_element(data.begin(), data.end(), comp_minx);
    auto min_x = getMinX(*poly_with_minx);

    auto comp_miny = std::bind(std::less<>{}, std::bind(getMinY, _1), std::bind(getMinY, _2));
    auto poly_with_miny = std::min_element(data.begin(), data.end(), comp_miny);
    auto min_y = getMinY(*poly_with_miny);

    auto comp_maxx = std::bind(std::less<>{}, std::bind(getMaxX, _1), std::bind(getMaxX, _2));
    auto poly_with_maxx = std::max_element(data.begin(), data.end(), comp_maxx);
    auto max_x = getMinX(*poly_with_maxx);

    auto comp_maxy = std::bind(std::less<>{}, std::bind(getMaxY, _1), std::bind(getMaxY, _2));
    auto poly_with_maxy = std::max_element(data.begin(), data.end(), comp_maxy);
    auto max_y = getMaxY(*poly_with_maxy);

    std::vector< Point > points_rect{{min_x, min_y}, {min_x, max_y},
                                     {max_x, max_y}, {max_x, min_y}};
    return Polygon{points_rect};
  }

  bool isInFrame(const std::vector< Polygon >& data, const Polygon& poly)
  {
    auto frame_data = getFrameRectForCompositeShapes(data);
    auto frame_poly = getFrameRect(poly);
    auto p1_data = frame_data.points[0];
    auto p1_poly = frame_poly.points[0];
    auto p2_data = frame_data.points[2];
    auto p2_poly = frame_poly.points[2];

    bool cond_1 = p1_poly.x >= p1_data.x && p1_poly.y >= p1_data.y;
    bool cond_2 = p2_poly.x <= p2_data.x && p2_poly.y <= p2_data.y;
    return cond_1 && cond_2;
  }
}
#endif
