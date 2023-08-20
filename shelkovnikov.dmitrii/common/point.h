#ifndef SPBSPU_LABS_2023_TP_904_POINT_H
#define SPBSPU_LABS_2023_TP_904_POINT_H
#include <istream>
namespace dimkashelk
{
  struct Point
  {
    int x, y;
  };
  struct AreaStorage
  {
    double operator()(const Point &lnr, const Point &rnl);
  };
  std::istream &operator>>(std::istream &in, Point &point);
}
#endif
