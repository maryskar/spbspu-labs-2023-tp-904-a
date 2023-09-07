#include "commands.hpp"
#include <numeric>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <functional>
#include <ScopeGuard.hpp>
bool litvin::isEven(const Polygon & polygon)
{
  return size(polygon) % 2 == 0;
}
bool litvin::isOdd(const Polygon & polygon)
{
  return !isEven(polygon);
}
void litvin::printEvenArea(const std::vector< Polygon > & data, std::ostream & out)
{
  std::vector< double > areas(data.size());
  using namespace std::placeholders;
  auto getAreaIfEven = std::bind(calcAreaIf, _1, isEven);
  std::transform(data.cbegin(), data.cend(), std::back_inserter(areas), getAreaIfEven);
  ScopeGuard guard(out);
  out << std::fixed << std::setprecision(1) << std::accumulate(areas.cbegin(), areas.cend(), 0.0) << '\n';
}
void litvin::printOddArea(const std::vector< Polygon > & data, std::ostream & out)
{
  std::vector< double > areas(data.size());
  using namespace std::placeholders;
  auto getAreaIfOdd = std::bind(calcAreaIf, _1, isOdd);
  std::transform(data.cbegin(), data.cend(), std::back_inserter(areas), getAreaIfOdd);
  ScopeGuard guard(out);
  out << std::fixed << std::setprecision(1) << std::accumulate(areas.cbegin(), areas.cend(), 0.0) << '\n';
}
void litvin::printAverageArea(const std::vector< Polygon > & data, std::ostream & out)
{
  if (data.empty())
  {
    throw std::invalid_argument("Empty dataset");
    return;
  }
  std::vector< double > areas(data.size());
  std::transform(data.cbegin(), data.cend(), std::back_inserter(areas), calcArea);
  double sum = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  ScopeGuard guard(out);
  out << std::fixed << std::setprecision(1) << sum / static_cast< double >(data.size()) << '\n';
}
bool litvin::hasQuantityOfVertexes(const Polygon & pol, size_t num)
{
  return size(pol) == num;
}
double litvin::calcAreaIfNVertexes(const Polygon & pol, size_t number_of_vertexes)
{
  return hasQuantityOfVertexes(pol, number_of_vertexes) ? calcArea(pol) : 0.0;
}
void litvin::printAreaIfNumberOfVertexesIs(const std::vector< Polygon > & data,
    size_t number_of_vertexes,
    std::ostream & out)
{
  if (number_of_vertexes < 3)
  {
    throw std::invalid_argument("Invalid command parameter");
    return;
  }
  std::vector< double > areas(data.size());
  using namespace std::placeholders;
  auto calcAreaNVertexes = std::bind(calcAreaIfNVertexes, _1, number_of_vertexes);
  std::transform(data.cbegin(), data.cend(), std::back_inserter(areas), calcAreaNVertexes);
  ScopeGuard guard(out);
  out << std::fixed << std::setprecision(1) << std::accumulate(areas.cbegin(), areas.cend(), 0.0) << '\n';
}
double litvin::getMaxOrMinAreaOrVertexes(const std::vector< Polygon > & data, bool isTheGreatest, bool isArea)
{
  std::vector< double > areas_or_vertexes(data.size());
  if (isArea)
  {
    std::transform(data.cbegin(), data.cend(), std::back_inserter(areas_or_vertexes), calcArea);
  }
  else
  {
    std::transform(data.cbegin(), data.cend(), std::back_inserter(areas_or_vertexes), size);
  }
  if (isTheGreatest)
  {
    return *(std::max_element(areas_or_vertexes.cbegin(), areas_or_vertexes.cend()));
  }
  return *(std::min_element(areas_or_vertexes.cbegin(), areas_or_vertexes.cend()));
}
void litvin::printIfMaxArea(const std::vector< Polygon > & data, std::ostream & out)
{
  if (!data.empty())
  {
    ScopeGuard guard(out);
    out << std::fixed << std::setprecision(1) << getMaxOrMinAreaOrVertexes(data, true, true) << '\n';
    return;
  }
  throw std::invalid_argument("For max area must be at least one polygon\n");
}
void litvin::printIfMaxVertexes(const std::vector< Polygon > & data, std::ostream & out)
{
  if (!data.empty())
  {
    out << getMaxOrMinAreaOrVertexes(data, true, false) << '\n';
    return;
  }
  throw std::invalid_argument("For max vertexes must be at least one polygon\n");
}
void litvin::printIfMinArea(const std::vector< Polygon > & data, std::ostream & out)
{
  if (!data.empty())
  {
    ScopeGuard guard(out);
    out << std::fixed << std::setprecision(1) << getMaxOrMinAreaOrVertexes(data, false, true) << '\n';
    return;
  }
  throw std::invalid_argument("For min area must be at least one polygon\n");
}
void litvin::printIfMinVertexes(const std::vector< Polygon > & data, std::ostream & out)
{
  if (!data.empty())
  {
    out << getMaxOrMinAreaOrVertexes(data, false, false) << '\n';
    return;
  }
  throw std::invalid_argument("For min vertexes must be at least one polygon\n");
}
size_t litvin::countIf(bool (* predicate)(const Polygon & pol), const std::vector< Polygon > & data)
{
  return std::count_if(data.cbegin(), data.cend(), predicate);
}
void litvin::printNumOfEven(const std::vector< Polygon > & data, std::ostream & out)
{
  out << countIf(isEven, data) << '\n';
}
void litvin::printNumOfOdd(const std::vector< Polygon > & data, std::ostream & out)
{
  out << countIf(isOdd, data) << '\n';
}
bool litvin::countIfNVertexes(const Polygon & pol, size_t num)
{
  return hasQuantityOfVertexes(pol, num);
}
void litvin::printNumOfPolygonsWithNumOfVertexes(const std::vector< Polygon > & data,
    size_t number_of_vertexes,
    std::ostream & out)
{
  if (number_of_vertexes < 3)
  {
    throw std::invalid_argument("Invalid command parameter");
  }
  using namespace std::placeholders;
  auto hasNVertexes = std::bind(countIfNVertexes, _1, number_of_vertexes);
  out << std::count_if(data.cbegin(), data.cend(), hasNVertexes) << '\n';
}
bool litvin::areLinesIntersected(const Point & l1_p1, const Point & l1_p2, const Point & l2_p1, const Point & l2_p2)
{
  double x1 = l1_p1.x;
  double y1 = l1_p1.y;
  double x2 = l1_p2.x;
  double y2 = l1_p2.y;
  double x3 = l2_p1.x;
  double y3 = l2_p1.y;
  double x4 = l2_p2.x;
  double y4 = l2_p2.y;
  double denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
  if (denominator == 0)
  {
    return false;
  }
  double intersectX = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denominator;
  double intersectY = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denominator;
  bool are_intersected_x1_x2 = intersectX >= std::min(x1, x2) && intersectX <= std::max(x1, x2);
  bool are_intersected_y1_y2 = intersectY >= std::min(y1, y2) && intersectY <= std::max(y1, y2);
  bool are_intersected_x3_x4 = intersectX >= std::min(x3, x4) && intersectX <= std::max(x3, x4);
  bool are_intersected_y3_y4 = intersectY >= std::min(y3, y4) && intersectY <= std::max(y3, y4);
  return are_intersected_x1_x2 && are_intersected_y1_y2 && are_intersected_x3_x4 && are_intersected_y3_y4;
}
bool litvin::arePolygonsIntersected(const Polygon & pol1, const Polygon & pol2)
{
  return std::any_of(pol1.points.cbegin(), pol1.points.cend() - 1, [&](const Point & p1)
  {
    return std::any_of(pol2.points.cbegin(), pol2.points.cend() - 1, [&](const Point & p2)
    {
      return areLinesIntersected(p1, *(pol1.points.cend() - 1), p2, *(pol2.points.cend() - 1));
    });
  });
}
void litvin::printNumberOfIntersections(const std::vector< Polygon > & data,
    const Polygon & pol,
    std::ostream & out)
{
  if (!data.empty())
  {
    using namespace std::placeholders;
    auto countIfIntersect = std::bind(arePolygonsIntersected, pol, _1);
    out << std::count_if(data.cbegin(), data.cend(), countIfIntersect) << '\n';
    return;
  }
  out << '0' << '\n';
}
bool litvin::minmax_predicate(const Point & p1, const Point & p2)
{
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}
bool litvin::arePolygonsSame(const Polygon & polygon1, const Polygon & polygon2)
{
  auto minmax_points1 = std::minmax_element(polygon1.points.begin(), polygon1.points.end(), minmax_predicate);
  auto minmax_points2 = std::minmax_element(polygon2.points.begin(), polygon2.points.end(), minmax_predicate);
  const auto & min1 = *(minmax_points1.first);
  const auto & max1 = *(minmax_points1.second);
  const auto & min2 = *(minmax_points2.first);
  const auto & max2 = *(minmax_points2.second);
  return min1.x <= max2.x && max1.x >= min2.x && min1.y <= max2.y && max1.y >= min2.y;
}
void litvin::printNumberOfSameFigures(const std::vector< Polygon > & data,
    const Polygon & pol,
    std::ostream & out)
{
  if (!data.empty())
  {
    using namespace std::placeholders;
    auto countIfSame = std::bind(arePolygonsSame, pol, _1);
    out << std::count_if(data.begin(), data.end(), countIfSame) << '\n';
    return;
  }
  out << '0' << '\n';
}
