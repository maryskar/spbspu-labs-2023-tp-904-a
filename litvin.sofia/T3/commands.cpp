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
    auto getArea = std::bind(calcAreaIf, isEven, _1);
    std::transform(data.cbegin(), data.cend(), std::back_inserter(areas), getArea);
    double res = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    return res;
  }
  double getOddArea(const v_pol & data)
  {
    std::vector< double > areas(data.size());
    using namespace std::placeholders;
    auto getArea = std::bind(calcAreaIf, isOdd, _1);
    std::transform(data.cbegin(), data.cend(), std::back_inserter(areas), getArea);
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
}
