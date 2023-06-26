#include "solvingCommands.h"
#include <algorithm>
#include <numeric>
#include <cmath>

namespace mashkin
{

  XMultiY::XMultiY(const mashkin::Point& first, const mashkin::Point& second):
    res(first.x * second.y)
  {
  }

  XMultiY::XMultiY(int&& rhs):
    res(rhs)
  {
  }

  XMultiY::XMultiY():
    res(0)
  {}

  XMultiY XMultiY::operator+(const XMultiY& rhs)
  {
    return XMultiY{this->res + rhs.res};
  }

  XMultiY solveXY(const Point& lhs, const Point& rhs)
  {
    return XMultiY(lhs, rhs);
  }

  PositiveArea::PositiveArea(const Polygon& lhs)
  {
    std::transform(lhs.points.begin(), --lhs.points.end(), ++lhs.points.begin(), std::back_inserter(this->halfArea), solveXY);
    std::transform(--lhs.points.end(), lhs.points.end(), lhs.points.begin(), std::back_inserter(this->halfArea), solveXY);
  }

  PositiveArea calcPositiveArea(const Polygon& lhs)
  {
    return PositiveArea(lhs);
  }

  NegativeArea::NegativeArea(const Polygon& lhs, const Polygon& rhs)
  {
    std::transform(++lhs.points.begin(), lhs.points.end(), rhs.points.begin(), std::back_inserter(this->halfArea), solveXY);
    std::transform(lhs.points.begin(), ++lhs.points.begin(), --rhs.points.end(), std::back_inserter(this->halfArea), solveXY);
  }

  NegativeArea calcNegativeArea(const Polygon& lhs)
  {
    auto rhs = lhs;
    return NegativeArea(lhs, rhs);
  }

  FullArea::FullArea(const PositiveArea& first, const NegativeArea& second)
  {
    XMultiY positive = std::accumulate(first.halfArea.begin(), first.halfArea.end(), XMultiY());
    XMultiY negative = std::accumulate(second.halfArea.begin(), second.halfArea.end(), XMultiY());
    int almostRes = std::abs(positive.res - negative.res);
    res = static_cast< double >(almostRes) * 0.5;
  }

  FullArea solveArea(const PositiveArea& first, const NegativeArea& second)
  {
    return FullArea(first, second);
  }
}
