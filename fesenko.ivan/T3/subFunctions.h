#ifndef CALCAREA_H
#define CALCAREA_H
#include <deque>
#include "polygon.h"
namespace fesenko
{
  using data_t = std::deque< Polygon >;
  double calcArea(double in, const Polygon &rhs);
  Polygon createBoundingRect(const data_t &data);
  Polygon createBoundingRect(const Polygon &rhs);

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

  struct isRect
  {
    bool operator()(const Polygon &rhs);
  };
}
#endif
