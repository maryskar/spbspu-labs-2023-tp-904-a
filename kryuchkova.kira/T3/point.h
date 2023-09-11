#ifndef POINT_H
#define POINT_H
#include <iostream>

namespace kryuchkova
{
  struct Point
  {
    int x, y;
  };

  std::istream & operator>>( std::istream & in, Point & pos);
}

#endif
