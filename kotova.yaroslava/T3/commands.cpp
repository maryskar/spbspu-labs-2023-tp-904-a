#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <iofmtguard.hpp>
#include "geomfigures.hpp"

namespace kotova
{
  bool isEven(const Polygon &polygon)
  {
    return polygon.points.size() % 2 ==0;
  }

  bool isOdd(const Polygon &polygon)
  {
    return !isEven(polygon);
  }

  bool calcNumVert(const Polygon &polygon, size_t cnt)
  {
    return polygon.points.size() == cnt;
  }

  bool compPointX(const Point &rhs, const Point &lhs)
  {
    return rhs.x > lhs.x;
  }

  bool compPointY(const Point &rhs, const Point &lhs)
  {
    return rhs.y > lhs.y;
  }

  bool compArea(const Polygon &rhs, const Polygon &lhs)
  {
    return getArea(lhs) < getArea(rhs);
  }

  bool compVer(const Polygon &rhs, const Polygon &lhs)
  {
    return lhs.points.size() < rhs.points.size();
  }

  bool equalPoints(const Point &rhs, const Point &lhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  Point movePoint(const Point &p1, const Point &p2)
  {
    if (compPointX(p1, p2))
    {
      if (compPointY(p1, p2))
      {
        return {p1.x - p2.x, p1.y - p2.y};
      }
      return;
    }
    return;
  }

  auto findPoints(const Polygon &dest)
  {
    auto xMinMax = std::minmax_element(dest.points.cbegin(), dest.points.cend(), compPointX);
    auto yMinMax = std::minmax_element(dest.points.cbegin(), dest.points.cend(), compPointY);
    Point lowerPoint{(*xMinMax.first).x, (*yMinMax.first).y};
    Point higherPoint{(*xMinMax.second).x, (*yMinMax.first).y};
    return std::make_pair(lowerPoint, higherPoint);
  }

  bool isSamePolygon(const Polygon &rhs, const Polygon &lhs)
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

  void areaEven(const std::vector< Polygon > &dest, std::ostream &out)
  {
    std::vector < double > area;
    std::transform(dest.begin(), dest.end(), std::back_inserter(area), isEven);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(area.begin(), area.end(), 0.0) << '\n';
  }

  void areaOdd(const std::vector< Polygon > &dest, std::ostream &out)
  {
    std::vector < double > area;
    std::transform(dest.begin(), dest.end(), std::back_inserter(area), isOdd);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(area.begin(), area.end(), 0.0) << '\n';
  }

  void areaMean(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      std::logic_error("error, there is no polygon");
    }
    std::vector < double > area;
    std::transform(dest.begin(), dest.end(), std::back_inserter(area), getArea);
    double finAreas = std::accumulate(area.begin(), area.end(), 0.0) / dest.size();
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << finAreas << '\n';
  }

  void areaNumVertexes(size_t n, const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (n < 3)
    {
      throw std::logic_error("error");
    }
    using namespace std::placeholders;
    std::vector < double > area;
    std::copy_if(dest.begin(), dest.end(), std::back_inserter(area), std::bind(calcNumVert, _1, n));
    std::transform(dest.begin(), dest.end(), std::back_inserter(area), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(area.begin(), area.end(), 0.0) << '\n';
  }

  void maxArea(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      std::logic_error("error, there is no polygon");
    }
    std::vector < double > area;
    std::copy_if(dest.begin(), dest.end(), std::back_inserter(area), compArea);
    std::transform(dest.begin(), dest.end(), std::back_inserter(area), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(area.begin(), area.end(), 0.0) << '\n';
  }

  void maxVertexes(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      std::logic_error("error, there is no polygon");
    }
    std::vector < double > area;
    std::copy_if(dest.begin(), dest.end(), std::back_inserter(area), compVer);
    std::transform(dest.begin(), dest.end(), std::back_inserter(area), calcNumVert);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(area.begin(), area.end(), 0.0) << '\n';
  }

  void minArea(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      std::logic_error("error, there is no polygon");
    }
    std::vector < double > area;
    std::copy_if(dest.begin(), dest.end(), std::back_inserter(area), (!compArea));
    std::transform(dest.begin(), dest.end(), std::back_inserter(area), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(area.begin(), area.end(), 0.0) << '\n';
  }

  void minVertexes(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      std::logic_error("error, there is no polygon");
    }
    std::vector < double > area;
    std::copy_if(dest.begin(), dest.end(), std::back_inserter(area), (!compVer));
    std::transform(dest.begin(), dest.end(), std::back_inserter(area), calcNumVert);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(area.begin(), area.end(), 0.0) << '\n';
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

  void isSame(const std::vector< Polygon > &dest, std::istream &in, std::ostream &out)
  {
    Polygon polygon;
    in >> polygon;
    if (!in)
    {
      throw std::logic_error("error");
    }
    using namespace std::placeholders;
    iofmtguard iofmtguard(out);
    out << std::count_if(dest.begin(), dest.end(), std::bind(isSamePolygon, _1, polygon)) << '\n';
  }
}
