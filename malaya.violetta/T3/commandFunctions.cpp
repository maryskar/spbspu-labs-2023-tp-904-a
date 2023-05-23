#include "commandFunctions.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>
#include <cmath>
#include "helpFunctions.hpp"

namespace malaya
{
  bool isEvenPoints(const Polygon & polygon)
  {
    return !(polygon.points.size() % 2);
  }
  bool isEqualToNum(const Polygon & polygon, size_t num)
  {
    return polygon.points.size() == num;
  }
  double areaEven(const Polygon & polygon)
  {
    return (isEvenPoints(polygon) ? getArea(polygon) : 0.0);
  }
  double areaOdd(const Polygon & polygon)
  {
    return (!isEvenPoints(polygon) ? getArea(polygon) : 0.0);
  }
  double areaNum(const Polygon & polygon, size_t num)
  {
    return (isEqualToNum(polygon, num) ? getArea(polygon) : 0.0);
  }
  template < class Predicate >
  void outArea(const std::vector< Polygon > & polygons, std::ostream & out, Predicate pred)
  {
    std::vector< double > values(polygons.size());
    std::transform(polygons.begin(), polygons.end(), values.begin(), pred);
    out << std::accumulate(values.begin(), values.end(), 0.0) << '\n';
  }
  void outAreaOdd(const std::vector< Polygon > & polygons, std::ostream & out)
  {
    outArea(polygons, out, areaOdd);
  }
  void outAreaEven(const std::vector< Polygon > & polygons, std::ostream & out)
  {
    outArea(polygons, out, areaEven);
  }
  void outAreaNum(const std::vector< Polygon > & polygons, size_t num, std::ostream & out)
  {
    using namespace std::placeholders;
    auto pred = std::bind(isEqualToNum, _1, num);
    outArea(polygons, out, pred);
  }
  template < class T >
  T minElem(const std::vector< T > & elems)
  {
    return *std::min_element(elems.begin(), elems.end());
  }

  template < class T >
  T maxElem(const std::vector< T > & elems)
  {
    return *std::min_element(elems.begin(), elems.end());
  }

  template < class Func >
  double minMaxArea(const std::vector< Polygon > & polygons, Func func)
  {
    std::vector< double > values(polygons.size());
    std::transform(polygons.begin(), polygons.end(), values.begin(), getArea);
    return func(values);
  }
  void outMinArea(const std::vector< Polygon > & data, std::ostream & out)
  {
    out << minMaxArea(data, minElem< double >) << '\n';
  }
  void outMaxArea(const std::vector< Polygon > & data, std::ostream & out)
  {
    out << minMaxArea(data, maxElem< double >) << '\n';
  }
  void outMeanArea(const std::vector< Polygon > & data, std::ostream & out)
  {
    if(data.empty())
    {
      invalidPrint(out);
      out << '\n';
      return;
    }
    std::vector< double > values(data.size());
    std::transform(data.begin(), data.end(), values.begin(), getArea);
    double sum = std::accumulate(values.begin(), values.end(), 0.0) / data.size();
    out << sum << '\n';
  }
  size_t getVertexes(const Polygon & polygon)
  {
    return polygon.points.size();
  }
  template < class Func >
  size_t minMaxVertexes(const std::vector< Polygon > & data, Func func)
  {
    std::vector< size_t > vertexes(data.size());
    std::transform(data.begin(), data.end(), vertexes.begin(), getVertexes);
    return func(vertexes);
  }
  void outMinVertexes(const std::vector< Polygon > & data, std::ostream & out)
  {
    out << minMaxVertexes(data, minElem < size_t >) << '\n';
  }
  void outMaxVertexes(const std::vector< Polygon > & data, std::ostream & out)
  {
    out << minMaxVertexes(data, minElem < size_t >) << '\n';
  }
  template < class Predicate >
  size_t count(const std::vector< Polygon > & data, Predicate pred)
  {
    return std::count_if(data.begin(), data.end(), pred);
  }
  void outCountEven(const std::vector< Polygon > & data, std::ostream & out)
  {
    out << count(data, isEvenPoints) << '\n';
  }
  void outCountOdd(const std::vector< Polygon > & data, std::ostream & out)
  {
    using namespace std::placeholders;
    auto func = std::bind(std::logical_not<>{}, std::bind(isEvenPoints, _1));
    out << count(data, func) << '\n';
  }
  void outCountNum(const std::vector< Polygon > & data, size_t num, std::ostream & out)
  {
    using namespace std::placeholders;
    auto func = std::bind(isEqualToNum, _1, num);
    out << count(data, func);
  }
  double findSide(const Point & point1, const Point & point2)
  {
    double firstSquare = (point1.x - point2.x) * (point1.x - point2.x);
    double secondSquare = (point1.y - point2.y) * (point1.y - point2.y);
    return std::sqrt(firstSquare + secondSquare);
  }
  bool isRectangle(const Polygon & polygon)
  {
    if(!isEqualToNum(polygon, 4ull))
    {
      return false;
    }
    double first = findSide(polygon.points[0], polygon.points[1]);
    double second = findSide(polygon.points[1], polygon.points[2]);
    double third = findSide(polygon.points[2], polygon.points[3]);
    double fourth = findSide(polygon.points[3], polygon.points[0]);
    double diagonal = findSide(polygon.points[0], polygon.points[2]);
    bool isRectangularTriangle = (first * first + second * second) == (diagonal * diagonal);
    return (first == third && second == fourth && isRectangularTriangle);
  }
  void rects(const std::vector< malaya::Polygon > & data, std::ostream & out)
  {
    out << std::count_if(data.begin(), data.end(), isRectangle) << '\n';
  }
  Polygon sortPoints(const Polygon & polygon)
  {
    std::vector< Point > points = polygon.points;
    std::sort(points.begin(), points.end(), PointComparator{});
    return Polygon{ points };
  }
  bool isIdentical(const Polygon & left, const Polygon & right)
  {
    return left.points == right.points;
  }
  void perms(const std::vector< Polygon > & data, std::ostream & out, const Polygon & polygon)
  {
    using namespace std::placeholders;
    std::vector< Polygon > temp(data.size());
    std::transform(data.begin(), data.end(), temp.begin(), sortPoints);
    Polygon tempPolygon = sortPoints(polygon);
    auto func = std::bind(isIdentical, _1, tempPolygon);
    out << std::count_if(temp.begin(), temp.end(), func) << '\n';
  }
}