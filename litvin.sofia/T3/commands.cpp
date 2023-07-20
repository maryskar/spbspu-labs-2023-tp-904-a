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
    return size(polygon) % 2 == 1;
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
    double res = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    return res;
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
}
