#include "commands.h"
#include <iomanip>
#include <numeric>
#include <functional>
#include <math.h>
#include <iofmtguard.h>
#include "Polygon.h"
namespace mishanina
{
  bool isEven(const Polygon &polygon)
  {
    return polygon.points.size() % 2 == 0;
  }
  bool isOdd(const Polygon &polygon)
  {
    return !isEven(polygon);
  }
  bool isCountOfVertexes(const Polygon &polygon, std::size_t num)
  {
    return (polygon.points.size() == num);
  }
  bool isEqualPolygon(const Polygon &lhs, const Polygon &rhs, const Polygon &polygon)
  {
    return (rhs.points == lhs.points) && (rhs.points == polygon.points);
  }
  std::size_t getNumOfVertexes(const Polygon &polygon)
  {
    return polygon.points.size();
  }
  double getSide(const Point &p1, const Point &p2)
  {
    return p1.x * p2.y - p1.y * p2.x;
  }
  double getArea(const Polygon &pol)
  {
    double area;
    std::vector< int > arr(pol.points.size());
    std::transform(pol.points.begin(), --pol.points.end(), ++pol.points.begin(), std::back_inserter(arr), getSide);
    area = std::accumulate(arr.begin(), arr.end(), 0.0);
    area += (--pol.points.end())->x * pol.points.begin()->y - pol.points.begin()->x * (--pol.points.end())->y;
    return std::abs(area) / 2.0;
  }
  double getTotalArea(const std::vector< Polygon > &pol)
  {
    std::vector< double > areas(pol.size());
    std::transform(pol.begin(), pol.end(), areas.begin(), getArea);
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
    return sum;
  }
  std::size_t getMaxMinVert(const std::vector< Polygon > &polygons, bool isMax)
  {
    std::vector<std::size_t> points(polygons.size());
    std::transform(polygons.begin(), polygons.end(), points.begin(), getNumOfVertexes);
    auto res = isMax ? std::max_element(points.begin(), points.end()) : std::min_element(points.begin(), points.end());
    return *res;
  }
  double getMaxMinArea(const std::vector< Polygon > &polygons, bool isMax)
  {
    std::vector<double> areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), getArea);
    auto res = isMax ? std::max_element(areas.begin(), areas.end()) : std::min_element(areas.begin(), areas.end());
    return *res;
  }
  std::vector< Polygon > getPolygonsWithNumOfVertexes(const std::vector< Polygon > &polygons, std::size_t num)
  {
    using namespace std::placeholders;
    auto countVertexes = std::bind(isCountOfVertexes, _1, num);
    std::vector< Polygon > result;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(result), countVertexes);
    return result;
  }
  double getSideF(const Point &p1, const Point &p2)
  {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
  }
  bool isParallelorgam(double side1, double side2, double side3, double side4)
  {
    return ((side1 == side3) && (side2 == side4));
  }
  bool isRectangle(const Polygon &polygon)
  {
    if (!isCountOfVertexes(polygon, 4ull))
    {
      return false;
    }
    double s1 = getSideF(polygon.points[0], polygon.points[1]);
    double s2 = getSideF(polygon.points[1], polygon.points[2]);
    double s3 = getSideF(polygon.points[2], polygon.points[3]);
    double s4 = getSideF(polygon.points[3], polygon.points[0]);
    double d1 = getSideF(polygon.points[0], polygon.points[2]);
    double d2 = getSideF(polygon.points[1], polygon.points[3]);
    return (isParallelorgam(s1, s2, s3, s4) && (d1 == d2));
  }
  template< class P >
  std::vector< Polygon > getPolygonsIf(const std::vector< Polygon > &polygons, P p)
  {
    std::vector< Polygon > polygonsIf;
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(polygonsIf), p);
    return polygonsIf;
  }
  template< class P >
  double getAreaIf(const std::vector< Polygon > &polygons, P p)
  {
    std::vector< Polygon > polygonsIf = getPolygonsIf(polygons, p);
    std::vector< double > areas(polygonsIf.size());
    std::transform(polygonsIf.begin(), polygonsIf.end(), areas.begin(), getArea);
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
    return sum;
  }
  template< class P >
  std::size_t getCountIf(const std::vector< Polygon > &polygons, P p)
  {
    std::vector< Polygon > polygonsIf = getPolygonsIf(polygons, p);
    std::size_t res = std::count_if(polygonsIf.begin(), polygonsIf.end(), p);
    return res;
  }
  void printAreaEven(const std::vector< Polygon > &polygons, std::ostream &out)
  {
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getAreaIf(polygons, isEven) << '\n';
  }
  void printAreaOdd(const std::vector< Polygon > &polygons, std::ostream &out)
  {
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getAreaIf(polygons, isOdd) << '\n';
  }
  void printAreaMean(const std::vector< Polygon > &polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("ERROR : polygons are empty");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getTotalArea(polygons) / polygons.size() << '\n';
  }
  void printAreaNumOfVertexes(const std::vector< Polygon > &polygons, std::ostream &out, std::size_t num)
  {
    if (num < 3)
    {
      throw std::invalid_argument("ERROR : invalid parameter");
    }
    std::vector< Polygon > polygonsNum = getPolygonsWithNumOfVertexes(polygons, num);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getTotalArea(polygonsNum) << '\n';
  }
  void printMaxArea(const std::vector< Polygon > &polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("ERROR : polygons are empty");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getMaxMinArea(polygons, true) << '\n';
  }
  void printMaxVertexes(const std::vector< Polygon > &polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("ERROR : polygons are empty");
    }
    iofmtguard iofmtguard(out);
    out << getMaxMinVert(polygons, true) << '\n';
  }
  void printMinArea(const std::vector< Polygon > &polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("ERROR : polygons are empty");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getMaxMinArea(polygons, false) << '\n';
  }
  void printMinVertexes(const std::vector< Polygon > &polygons, std::ostream &out)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("ERROR : polygons are empty");
    }
    iofmtguard iofmtguard(out);
    out << getMaxMinVert(polygons, false) << '\n';
  }
  void printCountEven(const std::vector< Polygon > &polygons, std::ostream &out)
  {
    iofmtguard iofmtguard(out);
    out << getCountIf(polygons, isEven) << '\n';
  }
  void printCountOdd(const std::vector< Polygon > &polygons, std::ostream &out)
  {
    iofmtguard iofmtguard(out);
    out << getCountIf(polygons, isOdd) << '\n';
  }
  void printCountNumOfVertexes(const std::vector< Polygon > &polygons, std::ostream &out, std::size_t num)
  {
    if (num < 3)
    {
      throw std::invalid_argument("ERROR : invalid parameter");
    }
    std::vector< Polygon > polNum = getPolygonsWithNumOfVertexes(polygons, num);
    iofmtguard iofmtguard(out);
    out << polNum.size() << '\n';
  }
  void printRects(const std::vector< Polygon > &polygons, std::ostream &out)
  {
    iofmtguard iofmtguard(out);
    out << getCountIf(polygons, isRectangle) << '\n';
  }
  void printRmecho(std::vector< Polygon > &polygons, std::ostream &out, std::istream &in)
  {
    Polygon target;
    in >> target;
    if (!in || target.points.size() < 3)
    {
      throw std::invalid_argument("Invalid rmecho");
    }
    using namespace std::placeholders;
    auto pred = std::bind(isEqualPolygon, _1, _2, target);
    auto end = std::unique(polygons.begin(), polygons.end(), pred);
    std::size_t res = std::distance(end, polygons.end());
    polygons.erase(end, polygons.end());
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << res << "\n";
  }
}
