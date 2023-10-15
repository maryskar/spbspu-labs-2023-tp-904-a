#include "minCommands.h"
#include <iostream>
#include "helpFunctions.h"

namespace aksenov
{
  void doMinArea(const std::vector< Polygon > &pol)
  {
    std::vector< double > areas = getArea(pol);
    auto minElementIter = std::min_element(areas.begin(), areas.end());
    auto out = std::ostream_iterator< double > (std::cout, "\n");
    std::copy(minElementIter, minElementIter + 1, out);
  }

  void doMinVertexes(const std::vector< Polygon > &pol)
  {
    std::vector< Polygon > pols = pol;
    std::vector< size_t > amountsOfVertexes;
    for (const Polygon &polygon : pols)
    {
      amountsOfVertexes.push_back(polygon.points.size());
    }
    auto minVertIter = std::min_element(amountsOfVertexes.begin(), amountsOfVertexes.end());
    auto out = std::ostream_iterator< size_t > (std::cout, "\n");
    std::copy(minVertIter, minVertIter + 1, out);
  }
}
