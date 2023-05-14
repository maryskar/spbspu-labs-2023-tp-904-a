#ifndef POINT_H
#define POINT_H
#include <istream>
struct Point
{
  int x;
  int y;
};
std::istream &operator>>(std::istream &in, Point &dest);
#endif
