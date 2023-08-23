#include "area-calc.hpp"

#include <functional>
#include <numeric>
#include <algorithm>
#include <vector>

#include "commands.hpp"
#include "point-struct.hpp"

namespace
{
  int mulPoint(const turkin::Point & lhs, const turkin::Point & rhs)
  {
    return lhs.x * rhs.y;
  }
}

double turkin::calcArea(const Polygon & rhs)
{
  std::vector< int > plusArea, minusArea;
  std::transform(rhs.points.cbegin(), --rhs.points.cend(), ++rhs.points.cbegin(), std::back_inserter(plusArea), mulPoint);
  std::transform(--rhs.points.end(), rhs.points.end(), rhs.points.begin(), std::back_inserter(plusArea), mulPoint);
  std::transform(++rhs.points.begin(), rhs.points.end(), rhs.points.begin(), std::back_inserter(minusArea), mulPoint);
  std::transform(rhs.points.begin(), ++rhs.points.begin(), --rhs.points.end(), std::back_inserter(minusArea), mulPoint);
  int positive = std::accumulate(plusArea.cbegin(), plusArea.cend(), 0);
  int negative = std::accumulate(minusArea.cbegin(), minusArea.cend(), 0);
  int result = std::abs(positive - negative);
  return static_cast< double >(result) * 0.5;
}

double turkin::oddArea(double in, const Polygon & rhs)
{
  return in + ((rhs.points.size() % 2 == 0) ? calcArea(rhs) : 0.0);
}

double turkin::evenArea(double in, const Polygon & rhs)
{
  return in + ((rhs.points.size() % 2 == 1) ? calcArea(rhs) : 0.0);
}

double turkin::numArea(double in, const Polygon & rhs);
