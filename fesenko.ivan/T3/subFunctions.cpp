#include "subFunctions.h"
#include <algorithm>
#include <numeric>
#include <functional>

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

int getX(const fesenko::Point &point)
{
  return point.x;
}

int getY(const fesenko::Point &point)
{
  return point.y;
}

std::vector< int > getXVector(const fesenko::Polygon &rhs)
{
  std::vector< int > xVector = {};
  std::transform(rhs.points.cbegin(), rhs.points.cend(), std::back_inserter(xVector), getX);
  return xVector;
}

std::vector< int > getYVector(const fesenko::Polygon &rhs)
{
  std::vector< int > yVector = {};
  std::transform(rhs.points.cbegin(), rhs.points.cend(), std::back_inserter(yVector), getY);
  return yVector;
}

int getMinX(const fesenko::Polygon &rhs)
{
  std::vector< int > vector = getXVector(rhs);
  return *std::min_element(vector.begin(), vector.end());
}

int getMaxX(const fesenko::Polygon &rhs)
{
  std::vector< int > vector = getXVector(rhs);
  return *std::max_element(vector.begin(), vector.end());
}

int getMinY(const fesenko::Polygon &rhs)
{
  std::vector< int > vector = getYVector(rhs);
  return *std::min_element(vector.begin(), vector.end());
}

int getMaxY(const fesenko::Polygon &rhs)
{
  std::vector< int > vector = getYVector(rhs);
  return *std::max_element(vector.begin(), vector.end());
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

fesenko::Polygon fesenko::createBoundingRect(const data_t &data)
{
  using namespace std::placeholders;
  if (data.empty()) {
    throw std::logic_error("Data is empty");
  }
  auto polygonMinX = std::bind(std::less<>{}, std::bind(getMinX, _1), std::bind(getMinX, _2));
  auto dataMinX = std::min_element(data.cbegin(), data.cend(), polygonMinX);
  auto minX = getMinX(*dataMinX);

  auto polygonMinY = std::bind(std::less<>{}, std::bind(getMinY, _1), std::bind(getMinY, _2));
  auto dataMinY = std::min_element(data.cbegin(), data.cend(), polygonMinY);
  auto minY = getMinY(*dataMinY);

  auto polygonMaxX = std::bind(std::less<>{}, std::bind(getMaxX, _1), std::bind(getMaxX, _2));
  auto dataMaxX = std::max_element(data.cbegin(), data.cend(), polygonMaxX);
  auto maxX = getMaxX(*dataMaxX);

  auto polygonMaxY = std::bind(std::less<>{}, std::bind(getMaxY, _1), std::bind(getMaxY, _2));
  auto dataMaxY = std::max_element(data.cbegin(), data.cend(), polygonMaxY);
  auto maxY = getMaxY(*dataMaxY);

  std::vector< Point > points{{minX, minY}, {minX, maxY}, {maxX, maxY}, {maxX, minY}};
  return Polygon{points};
}

fesenko::Polygon fesenko::createBoundingRect(const Polygon &rhs)
{
  int minX = getMinX(rhs);
  int maxX = getMaxX(rhs);
  int minY = getMinY(rhs);
  int maxY = getMaxY(rhs);
  std::vector< Point > points{{minX, minY}, {minX, maxY}, {maxX, maxY}, {maxX, minY}};
  return Polygon{points};
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
  Point one = rhs.points[0];
  Point two = rhs.points[1];
  Point three = rhs.points[2];
  Point four = rhs.points[3];
  return isRightAngle(one, two, three) && isRightAngle(two, three, four)
      && isRightAngle(three, four, one) && isRightAngle(four, one, two);
}

