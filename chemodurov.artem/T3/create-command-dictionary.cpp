#include "create-command-dictionary.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>

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
  void printAreaIf(const std::vector< Polygon > & data, std::ostream & out, P p)
  {
    std::vector< double > areas;
    std::transform(data.begin(), data.end(), std::back_inserter(areas), p);
    out << std::accumulate(areas.begin(), areas.end(), 0.0) << '\n';
  }

  void printAreaOdd(const std::vector< Polygon > & data, std::ostream & out)
  {
    printAreaIf(data, out, transIntoOddArea);
  }

  void printAreaEven(const std::vector< Polygon > & data, std::ostream & out)
  {
    printAreaIf(data, out, transIntoEvenArea);
  }

  void printAreaMean(const std::vector< Polygon > & data, std::ostream & out)
  {
    if (data.empty())
    {
      throw std::invalid_argument("For mean area must be at least one polygon");
    }
    std::vector< double > areas;
    std::transform(data.begin(), data.end(), std::back_inserter(areas), calcArea);
    double sum_area = std::accumulate(areas.begin(), areas.end(), 0.0);
    out << (sum_area / data.size()) << '\n';
  }

  double transIntoAreaNumOfVerts(const Polygon & pol, size_t num)
  {
    return (size(pol) == num) ? calcArea(pol) : 0.0;
  }

  void printAreaNumOfVerts(const std::vector< Polygon > & data, std::ostream & out, size_t num)
  {
    using namespace std::placeholders;
    auto trans = std::bind(transIntoAreaNumOfVerts, _1, num);
    printAreaIf(data, out, trans);
  }

  bool isLessArea(const Polygon & lhs, const Polygon & rhs)
  {
    return calcArea(lhs) < calcArea(rhs);
  }

  void printMaxArea(const std::vector< Polygon > & data, std::ostream & out)
  {
    auto it = std::max_element(data.begin(), data.end(), isLessArea);
    if (it == data.end())
    {
      throw std::invalid_argument("For max area must be at least one polygon");
    }
    out << calcArea(*it);
  }

  bool isLessVerts(const Polygon & lhs, const Polygon & rhs)
  {
    return size(lhs) < size(rhs);
  }

  void printMaxVerts(const std::vector< Polygon > & data, std::ostream & out)
  {
    auto it = std::max_element(data.begin(), data.end(), isLessVerts);
    if (it == data.end())
    {
      throw std::invalid_argument("For max vertexes must be at least one polygon");
    }
    out << size(*it);
  }
}
