#include "help_commands.h"
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iofmt_guard.h>

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

bool skarlygina::isPerm(const skarlygina::Polygon& first, const skarlygina::Polygon& poly)
{
  return std::is_permutation(poly.points.begin(), poly.points.end(), first.points.begin(), first.points.end());
}

bool isOdd(const skarlygina::Polygon& poly)
{
  return poly.points.size() % 2;
}

bool isEven(const skarlygina::Polygon& poly)
{
  return poly.points.size() % 2 - 1;
}

size_t skarlygina::countOdd(const std::vector< Polygon >& polys)
{
  return std::count_if(polys.begin(), polys.end(), isOdd);
}

size_t skarlygina::countEven(const std::vector< Polygon >& polys)
{
  auto odd = std::bind(isOdd, std::placeholders::_1);
  auto even_vert = std::bind(std::logical_not< bool >{}, odd);
  return std::count_if(polys.begin(), polys.end(), even_vert);
}

skarlygina::Point doOffset(skarlygina::Point point, skarlygina::Point offset)
{
  return point + offset;
}

bool isVert(const skarlygina::Polygon& poly, size_t number_vert)
{
  return poly.points.size() == number_vert;
}

size_t countNumOfVertexes(const std::vector< skarlygina::Polygon >& polys, size_t number_vert)
{
  if (number_vert < 3)
  {
    throw std::invalid_argument("Entered command is incorrect");
  }
  auto hasNumOfVert = std::bind(isVert, std::placeholders::_1, number_vert);
  return std::count_if(polys.begin(), polys.end(), hasNumOfVert);
}

bool skarlygina::isSame(const skarlygina::Polygon& first_poly, const skarlygina::Polygon& second_poly)
{
  std::vector< skarlygina::Point > first = first_poly.points;
  std::vector< skarlygina::Point > second = second_poly.points;
  if (first.size() != second.size())
  {
    return false;
  }
  skarlygina::Point offset{ first[0].x - second[0].x, first[0].y - second[0].y };
  std::vector< skarlygina::Point > second_new;

  auto off = std::bind(doOffset, std::placeholders::_1, offset);
  std::transform(second.begin(), second.end(), std::back_inserter(second_new), off);

  return first == second_new;

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