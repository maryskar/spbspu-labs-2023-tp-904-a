#ifndef POINT_H
#define POINT_H
#include <iostream>
namespace fesenko
{
  struct Point
  {
    int x, y;
  };
  std::istream &operator>>(std::istream &in, Point &rhs);
  std::ostream &operator<<(std::ostream &out, const Point &rhs);
}
#endif
