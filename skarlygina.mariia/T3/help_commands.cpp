#include "help_commands.h"
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iofmt_guard.h>
#include "help_structures.h"

double skarlygina::findAreaPoly(const skarlygina::Polygon& polys, double area)
{
  std::vector< skarlygina::Point > poly = polys.points;
  skarlygina::PolygonsArea area_polygon_count(*poly.rbegin());
  area += std::abs(std::accumulate(poly.begin(), poly.end(), 0.0, area_polygon_count)) / 2.0;
  return area;
}

bool isOdd(const skarlygina::Polygon& poly)
{
  return poly.points.size() % 2;
}

bool isEven(const skarlygina::Polygon& poly)
{
  return !(isOdd(poly));
}

bool isVert(const skarlygina::Polygon& poly, size_t number_vert)
{
  return poly.points.size() == number_vert;
}

double skarlygina::findAreaOdd(const std::vector< Polygon >& polys)
{
  using namespace std::placeholders;
  skarlygina::AreaCondition< std::function< bool(const skarlygina::Polygon&) > > odd_area(isOdd);
  return std::accumulate(polys.begin(), polys.end(), 0.0, odd_area);
}

double skarlygina::findAreaEven(const std::vector< Polygon >& polys)
{
  auto even_vert = std::bind(std::logical_not< bool >{}, std::bind(isOdd, std::placeholders::_1));
  AreaCondition< std::function< bool(const skarlygina::Polygon&) > > even_area(even_vert);
  return std::accumulate(polys.begin(), polys.end(), 0.0, even_area);
}

double skarlygina::findAreaMean(const std::vector< Polygon >& polys)
{
  if (polys.empty())
  {
    throw std::invalid_argument("Not enough figures");
  }
  auto getArea = std::bind(findAreaPoly, std::placeholders::_2, std::placeholders::_1);
  return std::accumulate(polys.begin(), polys.end(), 0.0, getArea) / polys.size();
}

double skarlygina::findAreaNumOfVertexes(const std::vector< Polygon >& polys, size_t count)
{
  if (count < 3)
  {
    throw std::invalid_argument("Entered command is incorrect");
  }
  auto number_vert = std::bind(isVert, std::placeholders::_1, count);
  AreaCondition< std::function< bool(const skarlygina::Polygon&) > > getArea(number_vert);
  return std::accumulate(polys.begin(), polys.end(), 0.0, getArea);
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

bool isSamePoint(const skarlygina::Point& first, const skarlygina::Point& second)
{
  return first.x == second.x && first.y == second.y;
}

skarlygina::Point moveOff(const skarlygina::Point& pos, int dx, int dy)
{
  return {pos.x - dx, pos.y - dy};
}

size_t skarlygina::countNumOfVertexes(const std::vector< skarlygina::Polygon >& polys, size_t number_vert)
{
  if (number_vert < 3)
  {
    throw std::invalid_argument("Entered command is incorrect");
  }
  auto hasNumOfVert = std::bind(isVert, std::placeholders::_1, number_vert);
  return std::count_if(polys.begin(), polys.end(), hasNumOfVert);
}

skarlygina::Polygon findStart(const skarlygina::Polygon& poly)
{
  int x_p = poly.points.front().x;
  int y_p = poly.points.front().y;
  auto move = std::bind(moveOff, std::placeholders::_1, x_p, y_p);
  std::vector< skarlygina::Point > moved(poly.points.size());
  std::transform(poly.points.begin(), poly.points.end(), std::back_inserter(moved), move);
  return skarlygina::Polygon{moved};
}

bool skarlygina::isSame(const skarlygina::Polygon& first_poly, const skarlygina::Polygon& second_poly)
{
  if (first_poly.points.size() != second_poly.points.size())
  {
    return false;
  }
  auto moved_first = findStart(first_poly);
  auto moved_second = findStart(second_poly);
  return std::equal(moved_first.points.begin(), moved_first.points.end(), moved_second.points.begin(), isSamePoint);
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
