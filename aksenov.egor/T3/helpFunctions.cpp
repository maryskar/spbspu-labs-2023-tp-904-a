#include "helpFunctions.h"
#include <vector>
#include <cstddef>
#include <cmath>
#include "polygon.h"
namespace aksenov
{
  std::vector< double > getArea(const std::vector<Polygon> &pol)
  {
    std::vector< double > areas;
    for (const Polygon &p: pol) {
      const std::vector< Point > &points = p.points;
      double firstSum = 0.0;
      double secondSum = 0.0;
      for (size_t i = 0; i < points.size(); i++) {
        const Point &current = points[i];
        const Point &next = points[(i + 1) % points.size()];
        firstSum += (static_cast< double >(next.y * current.x));
        secondSum += (static_cast< double >(next.x * current.y));
      }
      areas.push_back(std::fabs((firstSum - secondSum) / 2));
    }
    return areas;
  }
}