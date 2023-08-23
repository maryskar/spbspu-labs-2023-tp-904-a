#ifndef AREA_TYPE
#define AREA_TYPE

#include "point-struct.hpp"

namespace turkin
{
  double calcArea(double in, const Polygon & rhs);
  struct isOdd
  {
    bool operator()(const Polygon & rhs);
  };
  struct isEven
  {
    bool operator()(const Polygon & rhs);
  };
  struct isNum
  {
    explicit isNum(unsigned num);
    bool operator()(const Polygon & rhs);
    private:
      unsigned num_;
  };
}

#endif
