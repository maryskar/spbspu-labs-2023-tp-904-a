#include "commands.hpp"
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
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
    double res = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    return res;
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
    return sum / areas.size();
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
    double res = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    return res;
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
      return getMaxOrMinAreaOrVertexes(data, 1, 1);
    }
    throw std::invalid_argument("For max area must be at least one polygon\n");
  }
  double getMaxVertexes(const v_pol & data)
  {
    if (!data.empty())
    {
      getMaxOrMinAreaOrVertexes(data, 1, 0);
    }
    throw std::invalid_argument("For max vertexes must be at least one polygon\n");
  }
  double getMinArea(const v_pol & data)
  {
    if (!data.empty())
    {
      return getMaxOrMinAreaOrVertexes(data, 0, 1);
    }
    throw std::invalid_argument("For min area must be at least one polygon\n");
  }
  double getMinVertexes(const v_pol & data)
  {
    if (!data.empty())
    {
      return getMaxOrMinAreaOrVertexes(data, 0, 0);
    }
    throw std::invalid_argument("For min vertexes must be at least one polygon\n");
  }
  size_t countIf(bool (* predicate)(const Polygon & pol), const v_pol & data)
  {
    size_t count = std::count_if(data.cbegin(), data.cend(), predicate);
    return count;
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
    return hasQuantityOfVertexes(pol, num) ? true : false;
  }
  size_t countIfNOfVertexesIs(const v_pol & data, size_t number_of_vertexes)
  {
    using namespace std::placeholders;
    auto hasNVertexes = std::bind(countIfNVertexes, _1, number_of_vertexes);
    return std::count_if(data.cbegin(), data.cend(), hasNVertexes);
  }
}
