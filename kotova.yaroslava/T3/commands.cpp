#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <iofmtguard.hpp>
#include "geomfigures.hpp"

namespace kotova
{
  void outFalse(std::ostream& out)
  {
    out << "<FALSE>";
  }
  void outTrue(std::ostream& out)
  {
    out << "<TRUE>";
  }

  bool isEven(const Polygon &polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool isOdd(const Polygon &polygon)
  {
    return !isEven(polygon);
  }

  bool calcNumVert(const Polygon &polygon, size_t cnt)
  {
    return polygon.points.size() == cnt;
  }

  size_t isCntNumVert(const Polygon &pol)
  {
    return pol.points.size();
  }

  bool compPointX(const Point &lhs, const Point &rhs)
  {
    return rhs.x > lhs.x;
  }

  bool compPointY(const Point &lhs, const Point &rhs)
  {
    return rhs.y > lhs.y;
  }

  bool isLessArea(const Polygon &lhs, const Polygon &rhs)
  {
    return getArea(lhs) < getArea(rhs);
  }

  bool isGreaterArea(const Polygon &lhs, const Polygon &rhs)
  {
    return (!isLessArea(lhs, rhs));
  }

  bool isLessVer(const Polygon &lhs, const Polygon &rhs)
  {
    return lhs.points.size() < rhs.points.size();
  }

  bool isGreaterVer(const Polygon &lhs, const Polygon &rhs)
  {
    return (!isLessVer(lhs, rhs));
  }

  bool equalPoints(const Point &lhs, const Point &rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  Point movePoint(const Point &p1, const Point &p2)
  {
    return {p1.x - p2.x, p1.y - p2.y};
  }

  double getSumArea(double area, const Polygon &pol)
  {
    return area + getArea(pol);
  }

  double getAreaEven(const std::vector< Polygon > &dest)
  {
    using namespace std::placeholders;
    std::vector< Polygon > tmp;
    std::copy_if(dest.cbegin(), dest.cend(), std::back_inserter(tmp), std::bind(isEven, _1));
    double area = std::accumulate(tmp.cbegin(), tmp.cend(), 0, getSumArea);
    return area;
  }

  double getAreaOdd(const std::vector< Polygon > &dest)
  {
    using namespace std::placeholders;
    std::vector< Polygon > tmp;
    std::copy_if(dest.cbegin(), dest.cend(), std::back_inserter(tmp), std::bind(isOdd, _1));
    double area = std::accumulate(tmp.cbegin(), tmp.cend(), 0, getSumArea);
    return area;
  }

  template< typename P >
  double getMaxOrMinArea(const std::vector< Polygon > &pol, P p)
  {
    std::vector< Polygon >::const_iterator tmp = std::max_element(pol.cbegin(), pol.cend(), p);
    return getArea(*tmp);
  }

  template< typename P >
  size_t getMaxOrMinVer(const std::vector< Polygon > & pol, P p)
  {
    std::vector< Polygon >::const_iterator tmp = std::max_element(pol.cbegin(), pol.cend(), p);
    return isCntNumVert(*tmp);
  }

  auto findPoints(const Polygon &dest)
  {
    auto minX = std::min_element(dest.points.begin(), dest.points.end(), compPointX)->x;
    auto minY = std::min_element(dest.points.begin(), dest.points.end(), compPointY)->y;
    auto maxX = std::max_element(dest.points.begin(), dest.points.end(), compPointX)->x;
    auto maxY = std::max_element(dest.points.begin(), dest.points.end(), compPointY)->y;
    Point lowerPoint{minX, minY};
    Point higherPoint{maxX, maxY};
    return std::make_pair(lowerPoint, higherPoint);
  }

  bool isInFrame(const Polygon &polygon)
  {
    auto pol = findPoints(polygon);
    int polMinX = pol.first.x;
    int polMinY = pol.first.y;
    int polMaxX = pol.second.x;
    int polMaxY = pol.second.y;
    auto xPair = std::minmax_element(polygon.points.cbegin(), polygon.points.cend(), compPointX);
    auto yPair = std::minmax_element(polygon.points.cbegin(), polygon.points.cend(), compPointY);
    if (xPair.first->x <= polMinX && yPair.first->y <= polMinY && xPair.second->x >= polMaxX && yPair.second->y >= polMaxY)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool isSamePolygon(const Polygon &lhs, const Polygon &rhs)
  {
    if ((rhs.points.size() != lhs.points.size() || getArea(rhs) != getArea(lhs)))
    {
      return false;
    }
    auto rhsPoints = findPoints(rhs);
    auto lhsPoints = findPoints(lhs);
    Point lowerRhs{rhsPoints.first.x, rhsPoints.first.y};
    Point lowerLhs{lhsPoints.first.x, lhsPoints.first.y};
    Point higherRhs{rhsPoints.second.x, rhsPoints.second.y};
    Point higherlhs{lhsPoints.second.x, lhsPoints.second.y};
    auto diffHigher = movePoint(higherRhs, lowerRhs);
    auto diffLower = movePoint(higherlhs, lowerLhs);
    return equalPoints(diffHigher, diffLower);
  }

  auto isSameP(const std::vector< Polygon > &dest, const Polygon &pol)
  {
    using namespace std::placeholders;
    return std::count_if(dest.begin(), dest.end(), std::bind(isSamePolygon, _1, pol));
  }

  void areaEven(const std::vector< Polygon > &dest, std::ostream &out)
  {
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getAreaEven(dest) << '\n';
  }

  void areaOdd(const std::vector< Polygon > &dest, std::ostream &out)
  {
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getAreaOdd(dest) << '\n';
  }

  void areaMean(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    double area = std::accumulate(dest.cbegin(), dest.cend(), 0, getSumArea);
    area /= dest.size();
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << area << '\n';
  }

  void areaNumVertexes(size_t n, const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (n < 3)
    {
      throw std::logic_error("error");
    }
    using namespace std::placeholders;
    std::vector< Polygon > tmp(dest.size());
    std::copy_if(dest.begin(), dest.end(), tmp.begin(), std::bind(calcNumVert, _1, n));
    size_t cnt = std::count_if(dest.begin(), dest.end(), std::bind(calcNumVert, _1, n));
    std::vector< double > tmp_cnt(cnt);
    auto fin_num = tmp.begin() + cnt;
    std::transform(tmp.begin(), fin_num, tmp_cnt.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(tmp_cnt.begin(), tmp_cnt.end(), 0.0) << '\n';
  }

  void maxArea(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      throw std::logic_error("error, there is no polygon");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getMaxOrMinArea(dest, isLessArea) << '\n';
  }

  void maxVertexes(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      throw std::logic_error("error, there is no polygon");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getMaxOrMinVer(dest, isLessVer) << '\n';
  }

  void minArea(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      throw std::logic_error("error, there is no polygon");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getMaxOrMinArea(dest, isGreaterArea) << '\n';
  }

  void minVertexes(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      throw std::logic_error("error, there is no polygon");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getMaxOrMinVer(dest, isLessArea) << '\n';
  }

  void countEven(const std::vector< Polygon > &dest, std::ostream &out)
  {
    auto cnt = std::count_if(dest.begin(), dest.end(), isEven);
    iofmtguard iofmtguard(out);
    out << cnt << "\n";
  }

  void countOdd(const std::vector< Polygon > &dest, std::ostream &out)
  {
    auto cnt = std::count_if(dest.begin(), dest.end(), isOdd);
    iofmtguard iofmtguard(out);
    out << cnt << "\n";
  }

  void countNumVertexes(size_t n, const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (n < 3)
    {
      throw std::logic_error("error");
    }
    using namespace std::placeholders;
    iofmtguard iofmtguard(out);
    out << std::count_if(dest.begin(), dest.end(), std::bind(calcNumVert, _1, n)) << "\n";
  }

  void inFrame(const Polygon &pol, std::ostream &out)
  {
    (isInFrame(pol) ? outTrue(out) : outFalse(out));
  }

  void isSame(const std::vector< Polygon > &dest, const Polygon &pol, std::ostream &out)
  {
    if (!dest.empty())
    {
      out << isSameP(dest, pol) << '\n';
    }
    out << '0' << '\n';
  }
}
