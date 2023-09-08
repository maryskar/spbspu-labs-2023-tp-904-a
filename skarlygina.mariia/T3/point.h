#ifndef POINT_H
#define POINT_H
#include <ios>
namespace skarlygina
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream&, Point&);
  std::ostream& operator<<(std::ostream&, const Point&);
}
#endif
