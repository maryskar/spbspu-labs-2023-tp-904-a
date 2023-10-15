#include "helpFunctions.h"
#include <iostream>
#include <iterator>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include <numeric>
#include "polygon.h"
namespace timofeev
{
  using namespace std::placeholders;
  void printError(std::ostream &out)
  {
    out << "<INVALID COMMAND>" << "\n";
  }

  bool isOdd(const Polygon &polygon)
  {
    return polygon.points.size() % 2;
  }

  bool isEven(const Polygon &polygon)
  {
    return !(isOdd(polygon));
  }

  bool isEqual(const Polygon &pol, size_t val)
  {
    return pol.points.size() == val;
  }

  double getArea(const std::vector< Polygon > &pol, std::vector< double > &indivAreas)
  {
    double totalArea = 0.0;
    for (auto it = pol.begin(); it != pol.end(); ++it)
    {
      const Polygon &p = *it;
      const std::vector< Point > &points = p.points;
      double area = 0.0;
      double firstSum = 0.0;
      double secondSum = 0.0;
      for (size_t i = 0; i < points.size(); i++)
      {
        const Point &point1 = points[i];
        const Point &point2 = points[(i + 1) % points.size()];
        firstSum += (static_cast< double >(point1.x * point2.y));
        secondSum += (static_cast< double >(point1.y * point2.x));
      }
      area += firstSum - secondSum;
      totalArea += std::abs(area / 2.0);
      indivAreas.push_back(std::abs(area / 2.0));
    }
    return totalArea;
  }

  void doEven(const std::vector< Polygon > &res)
  {
    std::vector< Polygon > tmp (res.size());
    std::vector< double > individual;
    std::copy_if(res.begin(), res.end(), tmp.begin(), isEven);
    static_cast< void >(getArea(tmp, individual));
    double area = std::accumulate(individual.begin(), individual.end(), 0);
    std::cout << std::fixed << std::setprecision(1) << area << "\n";
  }

  void doOdd(const std::vector< Polygon > &res)
  {
    std::vector< Polygon > tmp (res.size());
    std::vector< double > individual;
    std::copy_if(res.begin(), res.end(), tmp.begin(), isOdd);
    static_cast< void >(getArea(tmp, individual));
    double area = std::accumulate(individual.begin(), individual.end(), 0);
    std::cout << std::fixed << std::setprecision(1) << area << "\n";
  }

  void doMean(const std::vector< Polygon > &res)
  {
    size_t amount = res.size();
    std::vector< double > individual;
    double area = getArea(res, individual);
    area /= amount;
    std::cout << std::fixed << std::setprecision(1) << area << "\n";
  }

  void doAreaV(const std::vector< Polygon > &res, size_t &val)
  {
    std::vector< Polygon > tmp (res.size());
    std::copy_if(res.begin(), res.end(), tmp.begin(), std::bind(isEqual, _1, val));
    std::vector< double > individual;
    double area = getArea(tmp, individual);
    std::cout << std::fixed << std::setprecision(1) << area << "\n";
  }

  void doMaxArea(const std::vector< Polygon > &res)
  {
    std::vector< Polygon > tmp = res;
    std::vector< double > individual;
    static_cast< void >(getArea(tmp, individual));
    if (individual.empty())
    {
      throw std::invalid_argument("invalid_argument");
    }
    double maxA = *std::max_element(individual.begin(), individual.end());
    std::cout << std::fixed << std::setprecision(1) << maxA << "\n";
  }

  bool comparePolygons(const Polygon &a, const Polygon &b)
  {
    return a.points.size() > b.points.size();
  }

  void doMaxV(const std::vector< Polygon > &res)
  {
    std::vector< Polygon > data = res;
    std::sort(data.begin(), data.end(), comparePolygons);

    std::vector< size_t > vertexCounts;
    for (const Polygon& polygon : data)
    {
      vertexCounts.push_back(polygon.points.size());
    }
    if (vertexCounts.empty())
    {
      throw std::invalid_argument("error");
    }
    size_t Vertex = *std::max_element(vertexCounts.begin(), vertexCounts.end());
    std::cout << std::fixed << std::setprecision(1) << Vertex << "\n";
  }

  void doMinArea(const std::vector< Polygon > &res)
  {
    std::vector< Polygon > tmp = res;
    std::vector< double > individual;
    static_cast< void >(getArea(tmp, individual));
    if (individual.empty())
    {
      throw std::invalid_argument("invalid_argument");
    }
    double minA = *std::min_element(individual.begin(), individual.end());
    std::cout << std::fixed << std::setprecision(1) << minA << "\n";
  }

  void doMinV(const std::vector< Polygon > &res)
  {
    std::vector< Polygon > data = res;
    std::sort(data.begin(), data.end(), comparePolygons);

    std::vector< size_t > vertexCounts;
    for (const Polygon& polygon : data)
    {
      vertexCounts.push_back(polygon.points.size());
    }
    size_t Vertex = *std::min_element(vertexCounts.begin(), vertexCounts.end());
    std::cout << std::fixed << std::setprecision(1) << Vertex << "\n";
  }

  void doCountEven(const std::vector< Polygon > &res)
  {
    size_t count = std::count_if(res.begin(), res.end(), isEven);
    std::cout << std::fixed << std::setprecision(1) << count << "\n";
  }

  void doCountOdd(const std::vector< Polygon > &res)
  {
    size_t count = std::count_if(res.begin(), res.end(), isOdd);
    std::cout << std::fixed << std::setprecision(1) << count << "\n";
  }

  void doCountV(const std::vector< Polygon >& res, size_t& val)
  {
    size_t Vertexes = std::count_if(res.begin(), res.end(), std::bind(isEqual, _1, val));
    std::cout << std::fixed << std::setprecision(1) << Vertexes << "\n";
  }

  int operator*(const Point &p1, const Point &p2)
  {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
  }

  double getCos(const Point &p1, const Point &p2, const Point &p3)
  {
    double side1x = p2.x - p1.x;
    double side1y = p2.y - p1.y;
    double side2x = p3.x - p2.x;
    double side2y = p3.y - p2.y;

    double scalar = side1x * side2x + side1y * side2y;

    double lengthSide1 = std::sqrt(side1x * side1x + side1y * side1y);
    double lengthSide2 = std::sqrt(side2x * side2x + side2y * side2y);

    double cos = scalar / (lengthSide1 * lengthSide2);

    return cos;
  }

  bool isAngle(const Polygon &pol)
  {
    const std::vector< Point >& points = pol.points;
    for (size_t i = 0; i < points.size(); i++)
    {
      const Point& p1 = points[i];
      const Point& p2 = points[(i + 1) % points.size()];
      const Point& p3 = points[(i + 2) % points.size()];

      double cosine = getCos(p1, p2, p3);

      if (std::abs(cosine) >= 0.01)
      {
        return false;
      }
    }
    return true;
  }

}
