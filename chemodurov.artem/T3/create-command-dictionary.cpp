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

  bool isEven(const Polygon & pol)
  {
    return !isOdd(pol);
  }

  double transIntoOddArea(const Polygon & pol)
  {
    return isOdd(pol) ? calcArea(pol) : 0.0;
  }

  double transIntoEvenArea(const Polygon & pol)
  {
    return isEven(pol) ? calcArea(pol) : 0.0;
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

  bool isNumOfVerts(const Polygon & pol, size_t num)
  {
    return size(pol) == num;
  }

  double transIntoAreaNumOfVerts(const Polygon & pol, size_t num)
  {
    return (isNumOfVerts(pol, num)) ? calcArea(pol) : 0.0;
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

  template< typename P1, typename P2 >
  void printMinOrMax(const std::vector< Polygon > & data, std::ostream & out, P1 p1, P2 p2)
  {
    auto it = std::max_element(data.begin(), data.end(), p1);
    if (it == data.end())
    {
      throw std::invalid_argument("For max area/vertexes must be at least one polygon");
    }
    out << p2(*it);
  }

  template< typename P >
  void printMaxOrMinArea(const std::vector< Polygon > & data, std::ostream & out, P p)
  {
    printMinOrMax(data, out, p, calcArea);
  }

  void printMaxArea(const std::vector< Polygon > & data, std::ostream & out)
  {
    printMaxOrMinArea(data, out, isLessArea);
  }

  void printMinArea(const std::vector< Polygon > & data, std::ostream & out)
  {
    using namespace std::placeholders;
    printMaxOrMinArea(data, out, std::bind(isLessArea, _2, _1));
  }

  bool isLessVerts(const Polygon & lhs, const Polygon & rhs)
  {
    return size(lhs) < size(rhs);
  }

  template< typename P >
  void printMaxOrMinVerts(const std::vector< Polygon > & data, std::ostream & out, P p)
  {
    printMinOrMax(data, out, p, size);
  }

  void printMaxVerts(const std::vector< Polygon > & data, std::ostream & out)
  {
    printMaxOrMinVerts(data, out, isLessVerts);
  }

  void printMinVerts(const std::vector< Polygon > & data, std::ostream & out)
  {
    using namespace std::placeholders;
    printMaxOrMinVerts(data, out, std::bind(isLessVerts, _2, _1));
  }

  template< typename P >
  void countIf(const std::vector< Polygon > & data, std::ostream & out, P p)
  {
    out << std::count_if(data.begin(), data.end(), p);
  }

  void countOdd(const std::vector< Polygon > & data, std::ostream & out)
  {
    countIf(data, out, isOdd);
  }

  void countEven(const std::vector< Polygon > & data, std::ostream & out)
  {
    countIf(data, out, isEven);
  }

  void countIfNumOfVerts(const std::vector< Polygon > & data, std::ostream & out, size_t num)
  {
    using namespace std::placeholders;
    auto pred = std::bind(isNumOfVerts, _1, num);
    countIf(data, out, pred);
  }
}
