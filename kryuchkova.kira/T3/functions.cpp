#include "functions.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include <iomanip>
#include "polygon.h"

namespace kryuchkova
{
  bool isEven(const Polygon & polygon)
  {
    return !(polygon.points.size() % 2);
  }

  bool isOdd(const Polygon & polygon)
  {
    return !(isEven(polygon));
  }

  bool isEqualNum(const Polygon & polygon, size_t num)
  {
    return polygon.points.size() == num;
  }

  double transIntoAreaNumOfVer(const Polygon & polygon, size_t num)
  {
    return (isEqualNum(polygon, num)) ? getArea(polygon) : 0.0;
  }

  bool isLessArea(const Polygon & lhs, const Polygon & rhs)
  {
    return getArea(lhs) < getArea(rhs);
  }

  bool isLessVer(const Polygon & lhs, const Polygon & rhs)
  {
    return lhs.points.size() < rhs.points.size();
  }

  double transIntoOddArea(const Polygon & polygon)
  {
    return isOdd(polygon) ? getArea(polygon) : 0.0;
  }

  double transIntoEvenArea(const Polygon & polygon)
  {
    return isEven(polygon) ? getArea(polygon) : 0.0;
  }

  template< typename P >
  void printAreaIf(const std::vector< Polygon > & temp, std::ostream & out, P p)
  {
    std::vector< double > areas;
    std::transform(temp.begin(), temp.end(), std::back_inserter(areas), p);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0) << '\n';
  }

  void printAreaEven(const std::vector< Polygon > & polygon, std::ostream & out)
  {
    printAreaIf(polygon, out, transIntoEvenArea);
  }

  void printAreaOdd(const std::vector< Polygon > & polygon, std::ostream & out)
  {
    printAreaIf(polygon, out, transIntoOddArea);
  }

  void printAreaMean(const std::vector< Polygon > & polygon, std::ostream & out)
  {
    if (polygon.empty())
    {
      throw std::invalid_argument("not enough polygons");
    }
    std::vector< double > areas;
    std::transform(polygon.begin(), polygon.end(), std::back_inserter(areas), getArea);
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << (sum / polygon.size()) << '\n';
  }

  void printAreaNumOfVer(const std::vector< Polygon > & polygon, std::ostream & out, size_t num)
  {
    if (num < 3)
    {
      throw std::invalid_argument("Invalid command");
    }
    using namespace std::placeholders;
    auto tr = std::bind(transIntoAreaNumOfVer, _1, num);
    printAreaIf(polygon, out, tr);
  }
  void printMaxArea(const std::vector< Polygon > & polygon, std::ostream & out);
  void printMaxVer(const std::vector< Polygon > & polygon, std::ostream & out);
  void printMinArea(const std::vector< Polygon > & polygon, std::ostream & out);
  void printMinVer(const std::vector< Polygon > & polygon, std::ostream & out);
  void printCountEven(const std::vector< Polygon > & polygon, std::ostream & out);
  void printCountOdd(const std::vector< Polygon > & polygon, std::ostream & out);
  void printCountNumOfVer(const std::vector< Polygon > & polygon, std::ostream & out, size_t num);
}