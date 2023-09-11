#include "help_commands.h"
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <functional>
#include "iofmt_guard.h"

namespace skarlygina
{
  struct PolygonsArea
  {
    PolygonsArea(skarlygina::Point point):
      prev(point)
    {}
    double operator()(double area, const skarlygina::Point& current)
    {
      area += static_cast< double >(prev.x) * current.y;
      area -= static_cast< double >(prev.y) * current.x;
      prev = current;
      return area;
    }
  private:
    skarlygina::Point prev;
  };
}

double skarlygina::findAreaPoly(const skarlygina::Polygon& polys, double area = 0.0)
{
  std::vector< skarlygina::Point > poly = polys.points;
  skarlygina::PolygonsArea area_polygon_count(*poly.rbegin());
  area += std::abs(std::accumulate(poly.begin(), poly.end(), 0.0, area_polygon_count)) / 2.0;
  return area;
}

bool compareArea(const skarlygina::Polygon& left, const skarlygina::Polygon& right)
{
  return skarlygina::findAreaPoly(left) < skarlygina::findAreaPoly(right);
}

bool compareVert(const skarlygina::Polygon& left, const skarlygina::Polygon& right)
{
  return left.points.size() < right.points.size();
}

size_t getSize(const skarlygina::Polygon poly)
{
  return poly.points.size();
}


double skarlygina::maxArea(const std::vector< Polygon >& polys)
{
  auto element_max_area = std::max_element(polys.begin(), polys.end(), compareArea);
  return findAreaPoly(*element_max_area);
}

size_t skarlygina::maxVertexes(const std::vector< Polygon >& polys)
{
  auto element_max_vert = std::max_element(polys.begin(), polys.end(), compareVert);
  return getSize(*element_max_vert);
}

double skarlygina::minArea(const std::vector< Polygon >& polys)
{
  auto element_min_area = std::min_element(polys.begin(), polys.end(), compareArea);
  return findAreaPoly(*element_min_area);
}

size_t skarlygina::minVertexes(const std::vector< Polygon >& polys)
{
  auto element_min_vert = std::max_element(polys.begin(), polys.end(), compareVert);
  return getSize(*element_min_vert);
}