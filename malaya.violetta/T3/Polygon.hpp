#ifndef T3_POLYGON_HPP
#define T3_POLYGON_HPP
#include <vector>
#include <ios>
namespace malaya
{
  struct Point
  {
    int x, y;
  };
  std::istream & operator>>(std::istream & in, Point & point);

  struct SeparatorPointIO
  {
    char sep;
  };
  std::istream & operator>>(std::istream & in, SeparatorPointIO & separator);

  struct DoubleIO
  {
    double& ref;
  };
  std::istream & operator>>(std::istream & in, DoubleIO & separator);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream & operator>>(std::istream & in, Polygon & polygon);
  double getArea(const Polygon & polygon);
}
#endif
