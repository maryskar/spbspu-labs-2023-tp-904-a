#ifndef PRED_COMP_HPP
#define PRED_COMP_HPP

#include "area-calc.hpp"
#include "data-structs.hpp"
#include <vector>

namespace turkin
{
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
    explicit isNum(std::size_t num);
    bool operator()(const Polygon & rhs);
    private:
      std::size_t num_;
  };

  struct isSizeLess
  {
    bool operator()(const Polygon & lhs, const Polygon & rhs);
  };

  struct isSizeGreater
  {
    bool operator()(const Polygon & lhs, const Polygon & rhs);
  };

  struct isAreaLess
  {
    bool operator()(const Polygon & lhs, const Polygon & rhs);
  };

  struct isAreaGreater
  {
    bool operator()(const Polygon & lhs, const Polygon & rhs);
  };

  struct isRightAngle
  {
    bool operator()(const Polygon & rhs);
  };
}

#endif
