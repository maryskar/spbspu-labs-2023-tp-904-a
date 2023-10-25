#include "maxCommands.h"
#include <iostream>
#include <iomanip>
#include "helpFunctions.h"

namespace aksenov
{
  void doMaxArea(const std::vector< Polygon > &pol)
  {
    if (pol.empty())
    {
      throw std::invalid_argument("empty polygon");
    }
    std::vector< double > areas = getArea(pol);
    double maxElemen = *std::max_element(areas.begin(), areas.end());
    std::cout << std::fixed << std::setprecision(1) << maxElemen << "\n";
  }

  void doMaxVertexes(const std::vector< Polygon > &pol)
  {
    if (pol.empty())
    {
      throw std::invalid_argument("empty polygon");
    }
    std::vector< size_t > amountsOfVertexes;
    std::transform(pol.begin(), pol.end(), std::back_inserter(amountsOfVertexes), CountVerticesInPolygon);
    auto maxVertIter = std::max_element(amountsOfVertexes.begin(), amountsOfVertexes.end());
    auto out = std::ostream_iterator< size_t > (std::cout, "\n");
    std::copy(maxVertIter, maxVertIter + 1, out);
  }
}
