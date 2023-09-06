#include "command.hpp"
#include "polygon.hpp"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <functional>


#include <iostream>

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

double sumArea(double cur, const hrushchev::Polygon& polygon)
{
  return cur + hrushchev::getArea(polygon);
}

bool isEven(const hrushchev::Polygon& polygon)
{
  return polygon.points_.size() % 2 == 0;
}

bool isOdd(const hrushchev::Polygon& polygon)
{
  return !isEven(polygon);
}

bool isNecessaryVertex(const hrushchev::Polygon& polygon, size_t count)
{
  return polygon.points_.size() == count;
}

double chooseGreatereArea(double cur, const hrushchev::Polygon& polygon)
{
  double area = hrushchev::getArea(polygon);
  return (cur > area) ? cur : area;
}

double chooseGreatereVertexes(double cur, const hrushchev::Polygon& polygon)
{
  size_t count = polygon.points_.size();
  return (cur > count) ? cur : count;
}

double chooseLessArea(double cur, const hrushchev::Polygon& polygon)
{
  double area = hrushchev::getArea(polygon);
  return (cur < area) ? cur : area;
}

double chooseLessVertexes(double cur, const hrushchev::Polygon& polygon)
{
  size_t count = polygon.points_.size();
  return (cur < count) ? cur : count;
}

bool isEqualPolygon(const hrushchev::Polygon& lhs, const hrushchev::Polygon& rhs, const hrushchev::Polygon& polygon)
{
  return (rhs == lhs) && (rhs == polygon);
}

bool isCompatiblePoints(const hrushchev::Point& lhs, const hrushchev::Point& rhs, long long dif_x, long long dif_y)
{
  return ((lhs.x_ - rhs.x_) == dif_x) && ((lhs.y_ - rhs.y_) == dif_y);
}

bool isCompatiblePolygons(const hrushchev::Polygon& lhs, const hrushchev::Polygon& rhs)
{
  size_t size = lhs.points_.size();
  if (size != rhs.points_.size())
  {
    return false;
  }
  long long dif_x = lhs.points_.front().x_ - rhs.points_.front().x_;
  long long dif_y = lhs.points_.front().y_ - rhs.points_.front().y_;
  std::vector< bool > result(size);
  using namespace std::placeholders;
  auto binary_op = std::bind(isCompatiblePoints, _1, _2, dif_x, dif_y);
  std::transform(lhs.points_.begin(), lhs.points_.end(), rhs.points_.begin(), result.begin(), binary_op);
  return size == result.size();
}

double hrushchev::getAreaEven(const std::vector< Polygon >& polygons)
{
  std::vector< Polygon > even_polygons;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(even_polygons), isEven);
  return std::accumulate(even_polygons.begin(), even_polygons.end(), 0.0, sumArea);
}
double hrushchev::getAreaOdd(const std::vector< Polygon >& polygons)
{
  std::vector< Polygon > odd_polygons;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(odd_polygons), isOdd);
  return std::accumulate(odd_polygons.begin(), odd_polygons.end(), 0.0, sumArea);
}

double hrushchev::getAreaMean(const std::vector< Polygon >& polygons)
{
  size_t count = polygons.size();
  return std::accumulate(polygons.begin(), polygons.end(), 0.0, sumArea) / count;
}

double hrushchev::getAreaVertexes(const std::vector< Polygon >& polygons, size_t count)
{
  std::vector< Polygon > vertexes_polygons;
  using namespace std::placeholders;
  auto pred = std::bind(isNecessaryVertex, _1, count);
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(vertexes_polygons), pred);
  return std::accumulate(vertexes_polygons.begin(), vertexes_polygons.end(), 0.0, sumArea);
}

double hrushchev::getMaxArea(const std::vector< Polygon >& polygons)
{
  return std::accumulate(polygons.begin(), polygons.end(), 0.0, chooseGreatereArea);
}

size_t hrushchev::getMaxVertexes(const std::vector< Polygon >& polygons)
{
  return std::accumulate(polygons.begin(), polygons.end(), 0.0, chooseGreatereVertexes);
}

double hrushchev::getMinArea(const std::vector< Polygon >& polygons)
{
  return std::accumulate(polygons.begin(), polygons.end(), getArea(polygons.front()), chooseLessArea);
}

size_t hrushchev::getMinVertexes(const std::vector< Polygon >& polygons)
{
  return std::accumulate(polygons.begin(), polygons.end(), polygons.front().points_.size(), chooseLessVertexes);
}

size_t hrushchev::getCountEven(const std::vector< Polygon >& polygons)
{
  return std::count_if(polygons.begin(), polygons.end(), isEven);
}
size_t hrushchev::getCountOdd(const std::vector< Polygon >& polygons)
{
  return std::count_if(polygons.begin(), polygons.end(), isOdd);
}

size_t hrushchev::getCountVertexes(const std::vector< Polygon >& polygons, size_t count)
{
  using namespace std::placeholders;
  auto pred = std::bind(isNecessaryVertex, _1, count);
  return count_if(polygons.begin(), polygons.end(), pred);
}

size_t hrushchev::rmEcho(std::vector< Polygon >& polygons, const Polygon& polygon)
{
  using namespace std::placeholders;
  auto pred = std::bind(isEqualPolygon, _1, _2, polygon);
  auto new_end = std::unique(polygons.begin(), polygons.end(), pred);
  size_t res = std::distance(new_end, polygons.end());
  polygons.erase(new_end, polygons.end());
  return res;
}

size_t hrushchev::getSame(std::vector< Polygon >& polygons, const Polygon& polygon)
{
  using namespace std::placeholders;
  auto pred = std::bind(isCompatiblePolygons, _1, polygon);
  return count_if(polygons.begin(), polygons.end(), pred);
}
