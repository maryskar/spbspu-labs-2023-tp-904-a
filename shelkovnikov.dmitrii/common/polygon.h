#ifndef SPBSPU_LABS_2023_TP_904_POLYGON_HPP
#define SPBSPU_LABS_2023_TP_904_POLYGON_HPP
#include <vector>
#include "point.h"
namespace dimkashelk
{
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream &operator>>(std::istream &in, Polygon &polygon);
}
#endif
