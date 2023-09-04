#ifndef DATA_STRUCTS_HPP
#define DATA_STRUCTS_HPP

#include <istream>
#include <vector>

namespace turkin
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  struct ReturnType
  {
    explicit ReturnType(std::size_t num);
    explicit ReturnType(double num);

    union
    {
      std::size_t uns;
      double db;
    } num_;
    char type_;
  };

  std::ostream & operator<<(std::ostream & out, const ReturnType & rt);
  std::istream & operator>>(std::istream & in, Point & rhs);
  std::istream & operator>>(std::istream & in, Polygon & rhs);

  bool operator==(const Point & lhs, const Point & rhs);
  bool operator==(const Polygon & lhs, const Polygon & rhs);
}

#endif
