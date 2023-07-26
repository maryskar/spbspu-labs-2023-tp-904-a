#include "commands.hpp"
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include <math.h>
#include "polygon.hpp"
namespace litvin
{
  using v_pol = std::vector< litvin::Polygon >;
  bool isEven(const Polygon & polygon)
  {
    return size(polygon) % 2 == 0;
  }
  bool isOdd(const Polygon & polygon)
  {
    return !isEven(polygon);
  }
  double getEvenArea(const v_pol & data)
  {
    std::vector< double > areas(data.size());
    using namespace std::placeholders;
    auto getAreaIfEven = std::bind(calcAreaIf, _1, isEven);
    std::transform(data.cbegin(), data.cend(), std::back_inserter(areas), getAreaIfEven);
    return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  }
  double getOddArea(const v_pol & data)
  {
    std::vector< double > areas(data.size());
    using namespace std::placeholders;
    auto getAreaIfOdd = std::bind(calcAreaIf, _1, isOdd);
    std::transform(data.cbegin(), data.cend(), std::back_inserter(areas), getAreaIfOdd);
    return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  }
  double getAverageArea(const v_pol & data)
  {
    std::vector< double > areas(data.size());
    std::transform(data.cbegin(), data.cend(), std::back_inserter(areas), calcArea);
    double sum = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    return sum / static_cast<double>(areas.size());
  }
  bool hasQuantityOfVertexes(const Polygon & pol, size_t num)
  {
    return size(pol) == num;
  }
  double calcAreaIfNVertexes(const Polygon & pol, size_t number_of_vertexes)
  {
    return hasQuantityOfVertexes(pol, number_of_vertexes) ? calcArea(pol) : 0.0;
  }
  double getAreaIfNVertexes(const v_pol & data, size_t number_of_vertexes)
  {
    std::vector< double > areas(data.size());
    using namespace std::placeholders;
    auto calcAreaNVertexes = std::bind(calcAreaIfNVertexes, _1, number_of_vertexes);
    std::transform(data.cbegin(), data.cend(), std::back_inserter(areas), calcAreaNVertexes);
    return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  }
  double getMaxOrMinAreaOrVertexes(const v_pol & data, bool isTheGreatest, bool isArea)
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
  double getMaxArea(const v_pol & data)
  {
    if (!data.empty())
    {
      return getMaxOrMinAreaOrVertexes(data, true, true);
    }
    throw std::invalid_argument("For max area must be at least one polygon\n");
  }
  double getMaxVertexes(const v_pol & data)
  {
    if (!data.empty())
    {
      getMaxOrMinAreaOrVertexes(data, true, false);
    }
    throw std::invalid_argument("For max vertexes must be at least one polygon\n");
  }
  double getMinArea(const v_pol & data)
  {
    if (!data.empty())
    {
      return getMaxOrMinAreaOrVertexes(data, false, true);
    }
    throw std::invalid_argument("For min area must be at least one polygon\n");
  }
  double getMinVertexes(const v_pol & data)
  {
    if (!data.empty())
    {
      return getMaxOrMinAreaOrVertexes(data, false, false);
    }
    throw std::invalid_argument("For min vertexes must be at least one polygon\n");
  }
  size_t countIf(bool (* predicate)(const Polygon & pol), const v_pol & data)
  {
    return std::count_if(data.cbegin(), data.cend(), predicate);
  }
  size_t countEven(const v_pol & data)
  {
    return countIf(isEven, data);
  }
  size_t countOdd(const v_pol & data)
  {
    return countIf(isOdd, data);
  }
  bool countIfNVertexes(const Polygon & pol, size_t num)
  {
    return hasQuantityOfVertexes(pol, num);
  }
  size_t countIfNOfVertexesIs(const v_pol & data, size_t number_of_vertexes)
  {
    using namespace std::placeholders;
    auto hasNVertexes = std::bind(countIfNVertexes, _1, number_of_vertexes);
    return std::count_if(data.cbegin(), data.cend(), hasNVertexes);
  }
  bool areLinesIntersected(const Point & l1_p1, const Point & l1_p2, const Point & l2_p1, const Point & l2_p2)
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
    return (intersectX >= std::min(x1, x2) && intersectX <= std::max(x1, x2) &&
            intersectY >= std::min(y1, y2) && intersectY <= std::max(y1, y2) &&
            intersectX >= std::min(x3, x4) && intersectX <= std::max(x3, x4) &&
            intersectY >= std::min(y3, y4) && intersectY <= std::max(y3, y4));
  }
  bool arePolygonsIntersected(const Polygon & pol1, const Polygon & pol2)
  {
    return std::any_of(pol1.points.cbegin(), pol1.points.cend() - 1, [&](const Point & p1)
    {
      return std::any_of(pol2.points.cbegin(), pol2.points.cend() - 1, [&](const Point & p2)
      {
        return areLinesIntersected(p1, *(pol1.points.cend() - 1), p2, *(pol2.points.cend() - 1));
      });
    });
  }
  size_t getNumberOfIntersections(const v_pol & data, const Polygon & pol)
  {
    size_t count = 0;
    if (!data.empty())
    {
      using namespace std::placeholders;
      auto countIfIntersect = std::bind(arePolygonsIntersected, pol, _1);
      count = std::count_if(data.cbegin(), data.cend(), countIfIntersect);
      return count;
    }
    return count;
  }
  bool minmax_predicate(const Point & p1, const Point & p2)
  {
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
  }
  bool arePolygonsSame(const Polygon & polygon1, const Polygon & polygon2)
  {
    auto minmax_points1 = std::minmax_element(polygon1.points.begin(), polygon1.points.end(), minmax_predicate);
    auto minmax_points2 = std::minmax_element(polygon2.points.begin(), polygon2.points.end(), minmax_predicate);
    const auto & min1 = *(minmax_points1.first);
    const auto & max1 = *(minmax_points1.second);
    const auto & min2 = *(minmax_points2.first);
    const auto & max2 = *(minmax_points2.second);
    return min1.x <= max2.x && max1.x >= min2.x && min1.y <= max2.y && max1.y >= min2.y;
  }
  size_t getNumberOfSameFigures(const v_pol & data, const Polygon & pol)
  {
    size_t count = 0;
    if (!data.empty())
    {
      using namespace std::placeholders;
      auto countIfSame = std::bind(arePolygonsSame, pol, _1);
      count = std::count_if(data.begin(), data.end(), countIfSame);
      return count;
    }
    return count;
  }
}
