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
  bool operator==(const Point& lhs, const Point& rhs);

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& inp, Polygon& data);
  bool operator==(const Polygon& lhs, const Polygon& rhs);

  size_t getSize(const Polygon& polygon);
  double getArea(const Polygon& polygon);

  using Frame = std::pair< Point, Point >;

  Frame getFrame(const Polygon& polygon);
  Frame getPolygonsFrame(const std::vector< Polygon > data);
  bool isFrameInFrame(const Frame& lhs, const Frame& rhs);

  bool isSame(Polygon lhs, Polygon rhs);
  size_t countAllSame(const std::vector< Polygon > data, const Polygon& figure);
}

#endif
