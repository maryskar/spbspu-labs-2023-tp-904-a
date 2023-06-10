#ifndef T3_POLYGON_H
#define T3_POLYGON_H
#include <vector>
#include <iomanip>

struct Point
{
  int x, y;
};
struct Polygon
{
  std::vector< Point > points;
};

struct DelimiterIO
{
  char symbol;
};

std::istream& operator>>(std::istream& in, Point& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);
std::istream& operator>>(std::istream& in, DelimiterIO&& dest);


#endif
