#ifndef POINT_STRUCT_HPP
#define POINT_STRUCT_HPP

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
  
  std::istream & operator>>(std::istream & in, Point & rhs);
  std::ostream & operator<<(std::ostream & out, Point & rhs);
  
  std::istream & operator>>(std::istream & in, Polygon & rhs);
  std::ostream & operator<<(std::ostream & out, Polygon & rhs);
}

#endif
