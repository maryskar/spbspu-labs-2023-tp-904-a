#ifndef POLYGON_H
#define POLYGON_H

#include <istream>
#include <vector>

namespace dmitriev
{
  struct Point
  {
    int x, y;
  };

  std::istream& operator>>(std::istream& inp, Point& data);

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& inp, Polygon& data);

  size_t getSize(const Polygon& polygon);
  double getArea(const Polygon& polygon);

}

#endif
