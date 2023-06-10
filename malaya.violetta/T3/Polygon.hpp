#ifndef T3_POLYGON_HPP
#define T3_POLYGON_HPP
#include <vector>
#include <iosfwd>
namespace malaya
{
  struct Point
  {
    int x, y;
  };
  std::istream & operator>>(std::istream & in, Point & point);
  bool operator==(const Point & left, const Point & right);
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream & operator>>(std::istream & in, Polygon & polygon);
  double getArea(const malaya::Polygon & polygon);
  struct areaCounter
  {
    double operator()(const Point & left, const Point & right);
  };
}
#endif
