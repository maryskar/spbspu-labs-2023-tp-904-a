#include "create-command-dictionary.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>

namespace chemodurov
{
  bool isOdd(const Polygon & pol)
  {
    return (size(pol) % 2 == 0);
  }

  double transIntoOddArea(const Polygon & pol)
  {
    return isOdd(pol) ? calcArea(pol) : 0.0;
  }

  double transIntoEvenArea(const Polygon & pol)
  {
    return (!isOdd(pol)) ? calcArea(pol) : 0.0;
  }

  template< typename P >
  void printAreaOddOrEven(const std::vector< Polygon > & data, std::ostream & out, P p)
  {
    std::vector< double > areas;
    std::transform(data.begin(), data.end(), std::back_inserter(areas), p);
    out << std::accumulate(areas.begin(), areas.end(), 0.0);
  }

  void printAreaOdd(const std::vector< Polygon > & data, std::ostream & out)
  {
    printAreaOddOrEven(data, out, transIntoOddArea);
  }

  void printAreaEven(const std::vector< Polygon > & data, std::ostream & out)
  {
    printAreaOddOrEven(data, out, transIntoEvenArea);
  }
}
