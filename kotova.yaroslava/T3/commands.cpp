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

  bool compArea(const Polygon &rhs, const Polygon &lhs)
  {
    return getArea(lhs) < getArea(rhs);
  }

  bool copmVer(const Polygon &rhs, const Polygon &lhs)
  {
    return lhs.points.size() < rhs.points.size();
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
      std::invalid_argument("error, there is no polygon");
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
}
