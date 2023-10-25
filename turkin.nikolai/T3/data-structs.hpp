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

  enum class RType
  {
    SIZE_T, DOUBLE
  };

  struct ReturnType
  {
    public:
      explicit ReturnType(std::size_t num);
      explicit ReturnType(double num);
      RType getType() const;
      std::size_t getNum() const;
      double getDouble() const;
    private:
      union
      {
        std::size_t uns;
        double db;
      } num_;
      RType type_;
  };

  std::ostream & operator<<(std::ostream & out, const ReturnType & rt);
  std::istream & operator>>(std::istream & in, Point & rhs);
  std::istream & operator>>(std::istream & in, Polygon & rhs);
  void operator>>(std::string & in, Polygon & rhs);

  bool operator==(const Point & lhs, const Point & rhs);
  bool operator==(const Polygon & lhs, const Polygon & rhs);
}

#endif
