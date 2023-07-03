#ifndef POINT_H
#define POINT_H
#include <istream>
namespace romanovich
{
  struct Point
  {
    int x;
    int y;
    Point &operator=(const Point &rhs);
  };
}
#endif
