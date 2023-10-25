#include "dict_functions.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include <iomanip>
#include <iofmtguard.h>
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
  void countIf(const std::vector< Polygon > & polygon, std::ostream & out, P p)
  {
    out << std::count_if(polygon.begin(), polygon.end(), p) << '\n';
  }

  template< typename P >
  double getMaxOrMinArea(const std::vector< Polygon > & polygon, P p)
  {
    std::vector< Polygon >::const_iterator temp = std::max_element(polygon.cbegin(), polygon.cend(), p);
    return getArea(*temp);
  }

  template< typename P >
  double getMaxOrMinVer(const std::vector< Polygon > & polygon, P p)
  {
    std::vector< Polygon >::const_iterator temp = std::max_element(polygon.cbegin(), polygon.cend(), p);
    return (*temp).points.size();
  }

  bool isFormRightAngles(const std::vector< Point > & pos, size_t n)
  {
    Point a = pos[n];
    Point b = pos[(n + 1) % pos.size()];
    Point c = pos[(n + 2) % pos.size()];
    return (b.x - a.x) * (c.x - b.x) + (b.y - a.y) * (c.y - b.y) == 0;
  }

  bool isEqualPoint(const Point & lhs, const Point & rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  Point movePoint(const Point & pos, int dx, int dy)
  {
    return {pos.x - dx, pos.y - dy};
  }

  Polygon moveToStartCoord(const Polygon & pol)
  {
    int dx = pol.points.front().x;
    int dy = pol.points.front().y;
    using namespace std::placeholders;
    auto func = std::bind(movePoint, _1, dx, dy);
    std::vector< Point > movedPos(pol.points.size());
    std::transform(pol.points.begin(), pol.points.end(), std::back_inserter(movedPos), func);
    return Polygon{movedPos};
  }

  bool isSamePol(const Polygon & lhs, const Polygon & rhs)
  {
    if (lhs.points.size() != rhs.points.size())
    {
      return false;
    }
    auto movedLhs = moveToStartCoord(lhs);
    auto movedRhs = moveToStartCoord(rhs);
    return std::equal(movedLhs.points.begin(), movedLhs.points.end(), movedRhs.points.begin(), isEqualPoint);
  }

  bool isRightAngles(const Polygon & pol)
  {
    using namespace std::placeholders;
    auto state = std::bind(isFormRightAngles, pol.points, _1);
    std::vector< size_t > index(pol.points.size());
    std::iota(index.begin(), index.end(), 0);
    return std::any_of(index.begin(), index.end(), state);
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
  void printMaxArea(const std::vector< Polygon > & polygon, std::ostream & out)
  {
    if (polygon.empty())
    {
      throw std::invalid_argument("not enough polygons");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getMaxOrMinArea(polygon, isLessArea) << '\n';
  }

  void printMaxVer(const std::vector< Polygon > & polygon, std::ostream & out)
  {
    if (polygon.empty())
    {
      throw std::invalid_argument("not enough polygons");
    }
    iofmtguard iofmtguard(out);
    out << std::setprecision(1) << getMaxOrMinVer(polygon, isLessVer) << '\n';
  }

  void printMinArea(const std::vector< Polygon > & polygon, std::ostream & out)
  {
    iofmtguard iofmtguard(out);
    using namespace std::placeholders;
    out << std::fixed << std::setprecision(1) << getMaxOrMinArea(polygon, std::bind(isLessArea, _2, _1)) << '\n';
  }

  void printMinVer(const std::vector< Polygon > & polygon, std::ostream & out)
  {
    iofmtguard iofmtguard(out);
    using namespace std::placeholders;
    out << std::setprecision(1) << getMaxOrMinArea(polygon, std::bind(isLessVer, _2, _1)) << '\n';
  }

  void printCountEven(const std::vector< Polygon > & polygon, std::ostream & out)
  {
    countIf(polygon, out, isEven);
  }

  void printCountOdd(const std::vector< Polygon > & polygon, std::ostream & out)
  {
    countIf(polygon, out, isOdd);
  }

  void printCountNumOfVer(const std::vector< Polygon > & polygon, std::ostream & out, size_t num)
  {
    if (num < 3)
    {
      throw std::invalid_argument("INVALID COMMAND");
    }
    using namespace std::placeholders;
    countIf(polygon, out, std::bind(isEqualNum, _1, num));
  }

  void printRightShapes(const std::vector< Polygon > & polygon, std::ostream & out)
  {
    out << std::count_if(polygon.begin(), polygon.end(), isRightAngles) << '\n';
  }

  void printSame(const std::vector< Polygon > & polygon, std::ostream & out, std::istream & in)
  {
    Polygon pol;
    in >> pol;
    if (!in)
    {
      throw std::logic_error("Invalid input");
    }
    using namespace std::placeholders;
    auto func = std::bind(isSamePol, _1, pol);
    iofmtguard iofmtguard(out);
    out << std::count_if(polygon.begin(), polygon.end(), func) << '\n';
  }
}
