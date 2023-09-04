#include "command.hpp"
#include "polygon.hpp"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <ostream>

double hrushchev::calcArea(const Point & left, const Point & right)
{
  return 0.5 * (left.x_ * right.y_ - right.x_ * left.y_);
}
double hrushchev::getArea(const Polygon & polygon)
{
  double res = 0.0;
  std::vector< double > values(polygon.points_.size());
  std::transform(polygon.points_.begin(), --polygon.points_.end(), ++polygon.points_.begin(), values.begin(), calcArea);
  res = std::accumulate(values.begin(), values.end(), 0.0);
  long long x1 = polygon.points_.back().x_;
  long long y1 = polygon.points_.back().y_;
  long long x2 = polygon.points_.front().x_;
  long long y2 = polygon.points_.front().y_;
  res += 0.5 * (x1 * y2 - y1 * x2);
  return std::abs(res);
}

void hrushchev::printAreaEven(std::ostream& out, const std::vector< Polygon >& polygons)
{

}