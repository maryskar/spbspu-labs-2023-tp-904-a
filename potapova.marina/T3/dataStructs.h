#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <vector>

namespace potapova
{
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
    char sign;
  };

  bool operator==(const Point& first, const Point& second) noexcept;
  bool operator==(const Polygon& first, const Polygon& second) noexcept;
}

#endif
