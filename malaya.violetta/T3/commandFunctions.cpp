#include "commandFunctions.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>
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
  void outArea(std::vector< malaya::Polygon > & polygons, std::ostream & out, Predicate pred)
  {
    std::vector< double > values;
    std::transform(polygons.begin(), polygons.end(), values.begin(), pred);
    out << std::accumulate(values.begin(), values.end(), 0.0) << '\n';
  }
  void outAreaOdd(std::vector< malaya::Polygon > & polygons, std::ostream & out)
  {
    outArea(polygons, out, areaOdd);
  }
  void outAreaEven(std::vector< malaya::Polygon > & polygons, std::ostream & out)
  {
    outArea(polygons, out, areaEven);
  }




  //template < typename Predicate >
  //double minMaxArea(std::vector< malaya::Polygon > data)
  //{
  //
  //}
  //double maxArea(std::vector< malaya::Polygon > data)
  //{
  //
  //}
}