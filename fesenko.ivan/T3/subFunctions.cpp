#include "subFunctions.h"
#include <algorithm>
#include <numeric>

int mulPoint(const fesenko::Point &lhs, const fesenko::Point &rhs)
{
  return lhs.x * rhs.y;
}

bool isRightAngle(const fesenko::Point &one, const fesenko::Point &two, const fesenko::Point &three)
{
  fesenko::Point vector1 = {two.x - one.x, two.y - one.y};
  fesenko::Point vector2 = {three.x - two.x, three.y - two.y};
  return vector1.x * vector2.x + vector1.y * vector2.y == 0;
}

double fesenko::calcArea(double in, const Polygon &rhs)
{
  std::vector< int > plusArea, minusArea;
  std::transform(rhs.points.cbegin(), --rhs.points.cend(), ++rhs.points.cbegin(), std::back_inserter(plusArea), mulPoint);
  std::transform(--rhs.points.cend(), rhs.points.cend(), rhs.points.cbegin(), std::back_inserter(plusArea), mulPoint);
  std::transform(++rhs.points.cbegin(), rhs.points.cend(), rhs.points.cbegin(), std::back_inserter(minusArea), mulPoint);
  std::transform(rhs.points.cbegin(), ++rhs.points.cbegin(), --rhs.points.cend(), std::back_inserter(minusArea), mulPoint);
  int positive = std::accumulate(plusArea.cbegin(), plusArea.cend(), 0);
  int negative = std::accumulate(minusArea.cbegin(), minusArea.cend(), 0);
  int result = std::abs(positive - negative);
  return in + (static_cast< double >(result) * 0.5);
}

bool fesenko::isOdd::operator()(const Polygon &rhs)
{
  return rhs.points.size() % 2 != 0;
}

bool fesenko::isEven::operator()(const Polygon &rhs)
{
  return rhs.points.size() % 2 == 0;
}

fesenko::isNumber::isNumber(size_t number):
  number_(number)
{}

bool fesenko::isNumber::operator()(const Polygon &rhs)
{
  return rhs.points.size() == number_;
}

bool fesenko::isAreaLess::operator()(const Polygon &lhs, const Polygon &rhs)
{
  return calcArea(0.0, lhs) < calcArea(0.0, rhs);
}

bool fesenko::isSizeLess::operator()(const Polygon &lhs, const Polygon &rhs)
{
  return lhs.points.size() < rhs.points.size();
}

bool fesenko::isRect::operator()(const Polygon &rhs)
{
  if (rhs.points.size() != 4) {
    return false;
  }
  fesenko::Point one = rhs.points[0];
  fesenko::Point two = rhs.points[1];
  fesenko::Point three = rhs.points[2];
  fesenko::Point four = rhs.points[3];
  return isRightAngle(one, two, three) && isRightAngle(two, three, four)
      && isRightAngle(three, four, one) && isRightAngle(four, one, two);
}
