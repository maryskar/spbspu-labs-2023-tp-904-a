#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <vector>

namespace azheganova
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
}

#endif