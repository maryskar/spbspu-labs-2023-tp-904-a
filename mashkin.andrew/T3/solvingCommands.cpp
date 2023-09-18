#include "solvingCommands.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iterator>
#include <iomanip>
#include <numeric>
#include <outputStructs.h>

namespace mashkin
{
  using namespace std::placeholders;

  std::vector< FullArea > getFullArea(const std::deque< Polygon >::iterator& begin,
      const std::deque< Polygon >::iterator& end)
  {
    auto cap = std::distance(begin, end);
    std::vector< mashkin::PositiveArea > halfPA;
    std::vector< mashkin::NegativeArea > halfNA;
    std::vector< mashkin::FullArea > area;
    halfPA.reserve(cap);
    halfNA.reserve(cap);
    area.reserve(cap);
    std::transform(begin, end, std::back_inserter(halfPA), calcPositiveArea);
    std::transform(begin, end, std::back_inserter(halfNA), calcNegativeArea);
    std::transform(halfPA.begin(), halfPA.end(), halfNA.begin(), std::back_inserter(area), solveArea);
    return area;
  }

  bool isOdd(const Polygon& data)
  {
    return data.points.size() % 2;
  }

  bool isEven(const Polygon& data)
  {
    return !(isOdd(data));
  }

  XMultiY::XMultiY(const Point& first, const Point& second):
    res(first.x * second.y)
  {
  }

  XMultiY::XMultiY():
    res(0)
  {
  }

  FullArea::FullArea():
    res(0.0)
  {
  }

  FullArea FullArea::operator+(const mashkin::FullArea& rhs)
  {
    res += rhs.res;
    return *this;
  }

  XMultiY XMultiY::operator+(const XMultiY& rhs)
  {
    res += rhs.res;
    return *this;
  }

  XMultiY solveXY(const Point& lhs, const Point& rhs)
  {
    return XMultiY(lhs, rhs);
  }

  PositiveArea::PositiveArea(const Polygon& lhs)
  {
    std::transform(lhs.points.begin(), --lhs.points.end(), ++lhs.points.begin(), std::back_inserter(halfArea), solveXY);
    std::transform(--lhs.points.end(), lhs.points.end(), lhs.points.begin(), std::back_inserter(halfArea), solveXY);
  }

  PositiveArea calcPositiveArea(const Polygon& lhs)
  {
    return PositiveArea(lhs);
  }

  NegativeArea::NegativeArea(const Polygon& lhs)
  {
    std::transform(++lhs.points.begin(), lhs.points.end(), lhs.points.begin(), std::back_inserter(halfArea), solveXY);
    std::transform(lhs.points.begin(), ++lhs.points.begin(), --lhs.points.end(), std::back_inserter(halfArea), solveXY);
  }

  NegativeArea calcNegativeArea(const Polygon& lhs)
  {
    return NegativeArea(lhs);
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

  std::ostream& operator<<(std::ostream& out, const FullArea& data)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << std::fixed << std::setprecision(1) << data.res;
    return out;
  }

  bool isEqual(const Polygon& data, size_t count)
  {
    return data.points.size() == count;
  }

  bool FullArea::operator<(const mashkin::FullArea& rhs)
  {
    return res < rhs.res;
  }

  bool isEqualPoints(Polygon& lhs, Polygon& rhs)
  {
    std::sort(lhs.points.begin(), lhs.points.end());
    return lhs.points == rhs.points;
  }

  Angle::Angle(const Polygon& rhs)
  {
    ang.reserve(rhs.points.size());
    std::transform(rhs.points.begin(), rhs.points.end(), std::back_inserter(ang), std::bind(getAngles, _1, rhs));
  }

  int getAngles(const Point& firstPoint, const Polygon& polygon)
  {
    auto firstIt = std::find(polygon.points.begin(), polygon.points.end(), firstPoint);
    Point secondPoint;
    Point thridPoint;
    if (firstIt + 1 == polygon.points.end())
    {
      secondPoint = *polygon.points.begin();
      thridPoint = *(polygon.points.begin() + 1);
    }
    else
    {
      secondPoint = *(firstIt + 1);
      if (firstIt + 2 == polygon.points.end())
      {
        thridPoint = *polygon.points.begin();
      }
      else
      {
        thridPoint = *(firstIt + 2);
      }
    }
    int firstHalfOfAngle = (firstPoint.x - secondPoint.x) * (secondPoint.x - thridPoint.x);
    int secondHalfOfAngle = (firstPoint.y - secondPoint.y) * (secondPoint.y - thridPoint.y);
    return firstHalfOfAngle + secondHalfOfAngle;
  }

  bool isRightShapes(const Polygon& lhs)
  {
    Angle angles(lhs);
    return std::find(angles.ang.begin(), angles.ang.end(), 0) != angles.ang.end();
  }
}
