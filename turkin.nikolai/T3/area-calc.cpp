#include "area-calc.hpp"

#include <numeric>
#include <algorithm>
#include <vector>

#include "point-struct.hpp"

namespace
{
  int mulPoint(const turkin::Point & lhs, const turkin::Point & rhs)
  {
    return lhs.x * rhs.y;
  }
}

double turkin::calcArea(double in, const Polygon & rhs)
{
  std::vector< int > plusArea, minusArea;
  std::transform(rhs.points.cbegin(), --rhs.points.cend(), ++rhs.points.cbegin(), std::back_inserter(plusArea), mulPoint);
  std::transform(--rhs.points.end(), rhs.points.end(), rhs.points.begin(), std::back_inserter(plusArea), mulPoint);
  std::transform(++rhs.points.begin(), rhs.points.end(), rhs.points.begin(), std::back_inserter(minusArea), mulPoint);
  std::transform(rhs.points.begin(), ++rhs.points.begin(), --rhs.points.end(), std::back_inserter(minusArea), mulPoint);
  int positive = std::accumulate(plusArea.cbegin(), plusArea.cend(), 0);
  int negative = std::accumulate(minusArea.cbegin(), minusArea.cend(), 0);
  int result = std::abs(positive - negative);
  return in + (static_cast< double >(result) * 0.5);
}

bool turkin::isOdd::operator()(const Polygon & rhs)
{
  return rhs.points.size() % 2 == 0;
}

bool turkin::isEven::operator()(const Polygon & rhs)
{
  return rhs.points.size() % 2 != 0;
}

turkin::isNum::isNum(unsigned num):
  num_(num)
{}

bool turkin::isNum::operator()(const Polygon & rhs)
{
  return rhs.points.size() == num_;
}
