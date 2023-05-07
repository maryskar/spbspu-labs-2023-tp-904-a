// INFRAME   SAME
#include <iostream>
#include <iterator>
#include <sstream>
#include "Geometry.h"

int main()
{
  using inIter = std::istream_iterator< ganiullin::Polygon >;
  auto outIter = std::ostream_iterator< ganiullin::Polygon >(std::cout, "\n");
  std::vector< ganiullin::Polygon > polygons;
  std::istringstream iss(
    "3 (0;1) (3;4) (5;6)"
    "4 (0;0) (0;1) (1;0) (1;1)");
  std::copy(inIter(iss), inIter(), std::back_inserter(polygons));
  std::copy(std::begin(polygons), std::end(polygons), outIter);
}
