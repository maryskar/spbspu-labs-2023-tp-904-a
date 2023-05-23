#include "commandFunctions.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>
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
  void outArea(const std::vector< malaya::Polygon > & polygons, std::ostream & out, Predicate pred)
  {
    std::vector< double > values(polygons.size());
    std::transform(polygons.begin(), polygons.end(), values.begin(), pred);
    out << std::accumulate(values.begin(), values.end(), 0.0) << '\n';
  }
  void outAreaOdd(const std::vector< malaya::Polygon > & polygons, std::ostream & out)
  {
    outArea(polygons, out, areaOdd);
  }
  void outAreaEven(const std::vector< malaya::Polygon > & polygons, std::ostream & out)
  {
    outArea(polygons, out, areaEven);
  }
  void outAreaNum(const std::vector< malaya::Polygon > & polygons, size_t num, std::ostream & out)
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

  template < class Predicate >
  double minMaxArea(const std::vector< malaya::Polygon > & polygons, Predicate pred)
  {
    std::vector< double > values(polygons.size());
    std::transform(polygons.begin(), polygons.end(), values.begin(), getArea);
    return pred(values);
  }
  void outMinArea(const std::vector< malaya::Polygon > & data, std::ostream & out)
  {
    out << minMaxArea(data, minElem< double >);
  }
  void outMaxArea(const std::vector< malaya::Polygon > & data, std::ostream & out)
  {
    out << minMaxArea(data, maxElem< double >);
  }
  void outMeanArea(const std::vector< malaya::Polygon > & data, std::ostream & out)
  {

  }
}