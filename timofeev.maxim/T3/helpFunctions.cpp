#include "helpFunctions.h"
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include "polygon.h"
namespace timofeev
{
  using namespace std::placeholders;
  using out =  std::ostream_iterator< double >;
  using outV =  std::ostream_iterator< size_t >;
  bool is_number(const std::string& s)
  {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
  }
  void printError(std::ostream& out)
  {
    out << "<INVALID COMMAND>" << "\n";
  }

  bool isOdd(const Polygon& polygon)
  {
    return polygon.points.size() % 2;
  }

  bool isEven(const Polygon& polygon)
  {
    return !(isOdd(polygon));
  }

  bool isEqual(const Polygon &pol, size_t val)
  {
    return pol.points.size() == val;
  }

  bool isNotEqual(const Polygon &pol, size_t val)
  {
    return pol.points.size() != val;
  }

  double getArea(const std::vector<Polygon> &pol, std::vector< double > &indivAreas)
  {
    /*
     * (0 0)
     * (0 2)  0*2+0*2+2*0+0*0
     * (2 2)  0*0+2*2+2*2+2*0
     * (2 0)
     */
    double totalArea = 0.0;
    for (auto it = pol.begin(); it != pol.end(); ++it)
    {
      const Polygon &p = *it;
      const std::vector<Point> &points = p.points;
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
      totalArea += area;
      indivAreas.push_back(std::abs(area / 2.0));
    }
    return std::abs(totalArea) / 2.0;
  }

  void doEven(const std::vector< Polygon >& res)
  {
    std::vector< Polygon > tmp (res.size());
    std::vector<double> individual;
    std::copy_if(res.begin(), res.end(), tmp.begin(), isEven);
    double area = getArea(tmp, individual);
    std::vector< double > vec;
    vec.push_back(area);
    std::copy(vec.begin(), vec.end(),out(std::cout, "\n"));
  }

  void doOdd(const std::vector< Polygon >& res)
  {
    std::vector< Polygon > tmp (res.size());
    std::vector<double> individual;
    std::copy_if(res.begin(), res.end(), tmp.begin(), isOdd);
    double area = getArea(tmp, individual);
    std::vector< double > vec;
    vec.push_back(area);
    std::copy(vec.begin(), vec.end(),out(std::cout, "\n"));
  }

  void doMean(const std::vector< Polygon >& res)
  {
    size_t amount = res.size();
    std::vector< Polygon > tmp (res.size());
    std::vector<double> individual;
    double area = getArea(tmp, individual);
    area /= amount;
    std::vector< double > vec;
    vec.push_back(area);
    std::copy(vec.begin(), vec.end(),out(std::cout, "\n"));
  }

  void doAreaV(const std::vector< Polygon >& res, size_t& val)
  {
    std::vector< Polygon > tmp = res;
    std::remove_if(tmp.begin(), tmp.end(), std::bind(isNotEqual, _1, val));
    std::vector<double> individual;
    double area = getArea(tmp, individual);
    std::vector< double > vec;
    vec.push_back(area);
    std::copy(vec.begin(), vec.end(),out(std::cout, "\n"));
  }

  void doMaxArea(const std::vector< Polygon >& res)
  {
    std::vector< Polygon > tmp = res;
    std::vector<double> individual;
    double area = getArea(tmp, individual);
    double maxA = *std::max_element(individual.begin(), individual.end());
    std::vector< double > vec;
    vec.push_back(maxA);
    std::copy(vec.begin(), vec.end(),out(std::cout, "\n"));
  }

  bool comparePolygons(const Polygon& a, const Polygon& b)
  {
    return a.points.size() > b.points.size();
  }

  void doMaxV(const std::vector< Polygon >& res)
  {
    std::vector< Polygon > data = res;
    std::sort(data.begin(), data.end(), comparePolygons);

    std::vector<size_t> vertexCounts;
    for (const Polygon& polygon : data)
    {
      vertexCounts.push_back(polygon.points.size());
    }
    size_t Vertex = *std::max_element(vertexCounts.begin(), vertexCounts.end());
    std::vector< size_t > vec;
    vec.push_back(Vertex);
    std::copy(vec.begin(), vec.end(), outV(std::cout, "\n"));
  }

  void doMinArea(const std::vector< Polygon >& res)
  {
    std::vector< Polygon > tmp = res;
    std::vector<double> individual;
    double area = getArea(tmp, individual);
    double minA = *std::min_element(individual.begin(), individual.end());
    std::vector< double > vec;
    vec.push_back(minA);
    std::copy(vec.begin(), vec.end(),out(std::cout, "\n"));
  }

  void doMinV(const std::vector< Polygon >& res)
  {
    std::vector< Polygon > data = res;
    std::sort(data.begin(), data.end(), comparePolygons);

    std::vector<size_t> vertexCounts;
    for (const Polygon& polygon : data)
    {
      vertexCounts.push_back(polygon.points.size());
    }
    size_t Vertex = *std::min_element(vertexCounts.begin(), vertexCounts.end());
    std::vector< size_t > vec;
    vec.push_back(Vertex);
    std::copy(vec.begin(), vec.end(), outV(std::cout, "\n"));
  }

  void doСountEven(const std::vector< Polygon >& res)
  {
    size_t count = std::count_if(res.begin(), res.end(), isEven);
    std::vector< size_t > vec;
    vec.push_back(count);
    std::copy(vec.begin(), vec.end(), outV(std::cout, "\n"));
  }

  void doCountOdd(const std::vector< Polygon >& res)
  {
    size_t count = std::count_if(res.begin(), res.end(), isOdd);
    std::vector< size_t > vec;
    vec.push_back(count);
    std::copy(vec.begin(), vec.end(), outV(std::cout, "\n"));
  }

  void doCountV(const std::vector< Polygon >& res, size_t& val)
  {
    size_t Vertexes = std::count_if(res.begin(), res.end(), std::bind(isEqual, _1, val));
    std::vector< size_t > vec;
    vec.push_back(Vertexes);
    std::copy(vec.begin(), vec.end(), outV(std::cout, "\n"));
  }

  int operator*(const Point &p1, const Point &p2)
  {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
  }

  bool isSquareTriangle(const Point &p1, const Point &p2, const Point &p3)
  {
    return (p1 * p2 + p1 * p3) == p2 * p3;
  }

  bool isRectangle(const Polygon& pol)
  {
    if (pol.points.size() == 4)
    {
      Point p1 = pol.points[0];
      Point p2 = pol.points[1];
      Point p3 = pol.points[2];
      Point p4 = pol.points[3];
      return isSquareTriangle(p1, p2, p3) && isSquareTriangle(p4, p2, p3);
    }
    return false;
  }
  void doRSCommand(std::istream &in, const std::vector< Polygon >& res)
  {
    size_t val = std::count_if(res.begin(), res.end(), isRectangle);
    std::vector< size_t > vec;
    vec.push_back(val);
    std::copy(vec.begin(), vec.end(), outV(std::cout, "\n"));
  }
}
