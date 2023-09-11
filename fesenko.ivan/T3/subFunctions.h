#ifndef CALCAREA_H
#define CALCAREA_H
#include "polygon.h"
namespace fesenko
{
  double calcArea(double in, const Polygon &rhs);

  struct isOdd
  {
    bool operator()(const Polygon &rhs);
  };

  struct isEven
  {
    bool operator()(const Polygon &rhs);
  };

  struct isNumber
  {
    explicit isNumber(size_t number);
    bool operator()(const Polygon &rhs);
   private:
    size_t number_;
  };

  struct isAreaLess
  {
    bool operator()(const Polygon &lhs, const Polygon &rhs);
  };

  struct isSizeLess
  {
    bool operator()(const Polygon &lhs, const Polygon &rhs);
  };
}
#endif
