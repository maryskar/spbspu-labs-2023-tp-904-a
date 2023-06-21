#include "solvingCommands.h"

namespace mashkin
{

  XMultiY::XMultiY(const mashkin::Point& first, const mashkin::Point& second)
  {
    res = first.x * second.y;
  }

  XMultiY solveXY(const Point& lhs, const Point& rhs)
  {
    return XMultiY(lhs, rhs);
  }

  PositiveArea::PositiveArea(const Polygon& lhs, const Polygon& rhs)
  {
    std::transform(lhs.points.begin(), --lhs.points.end(), ++rhs.points.begin(), this->halfArea.begin(), solveXY);
  }

  PositiveArea calcPositiveArea(const Polygon& lhs)
  {
    auto rhs = lhs;
    return PositiveArea(lhs, rhs);
  }

  NegativeArea::NegativeArea(const Polygon& lhs, const Polygon& rhs)
  {
    std::transform(++lhs.points.begin(), lhs.points.end(), rhs.points.begin(), this->halfArea.begin(), solveXY);
  }

  NegativeArea calcNegativeArea(const Polygon& lhs)
  {
    auto rhs = lhs;
    return NegativeArea(lhs, rhs);
  }

  FullArea::FullArea(const PositiveArea& first, const NegativeArea& second)
  {
    res = static_cast< double >(first.halfArea.begin()->res - second.halfArea.begin()->res);
  }

  FullArea solveArea(const PositiveArea& first, const NegativeArea& second)
  {
    return FullArea(first, second);
  }
}
