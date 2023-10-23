#include "functions.h"
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>

bool gudkov::isEvenVertexesCount(const Polygon &polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool gudkov::isOddVertexesCount(const Polygon &polygon)
{
  return !isEvenVertexesCount(polygon);
}

bool gudkov::isEqualVertexesCount(const Polygon &polygon, size_t count)
{
  return polygon.points.size() == count;
}

bool gudkov::isLessByArea(const Polygon &a, const Polygon &b)
{
  return getArea(a) < getArea(b);
}

bool gudkov::isLessByVertexes(const Polygon &a, const Polygon &b)
{
  return a.points.size() < b.points.size();
}

bool gudkov::isLessPoints(const Point &a, const Point &b)
{
  if (a.x != b.x)
  {
    return a.x < b.x;
  }
  return a.y < b.y;
}

bool gudkov::isEqualCoordinates(const Point &a, const Point &b)
{
  return ((a.x == b.x && a.y == b.y) || (a.x == b.y && a.y == b.x));
}

bool gudkov::isEqualPolygons(const Polygon &a, const Polygon &b)
{
  if (a.points.size() != b.points.size())
  {
    return false;
  }

  std::vector< Point > copy_a;
  std::copy(std::begin(a.points), std::end(a.points), back_inserter(copy_a));
  std::sort(std::begin(copy_a), std::end(copy_a), isLessPoints);

  std::vector< Point > copy_b;
  std::copy(std::begin(b.points), std::end(b.points), back_inserter(copy_b));
  std::sort(std::begin(copy_b), std::end(copy_b), isLessPoints);

  return std::equal(std::begin(copy_a), std::end(copy_a), std::begin(copy_b), isEqualCoordinates);
}

double gudkov::calcAreaEven(const std::vector< Polygon > &data)
{
  std::vector< Polygon > even;
  std::copy_if(std::begin(data), std::end(data), back_inserter(even), isEvenVertexesCount);

  std::vector< double > squares;
  std::transform(std::begin(even), std::end(even), back_inserter(squares), getArea);

  double sum = std::accumulate(std::begin(squares), std::end(squares), 0.0);

  return sum;
}

double gudkov::calcAreaOdd(const std::vector< Polygon > &data)
{
  std::vector< Polygon > odd;
  std::copy_if(std::begin(data), std::end(data), back_inserter(odd), isOddVertexesCount);

  std::vector< double > squares;
  std::transform(std::begin(odd), std::end(odd), back_inserter(squares), getArea);

  double sum = std::accumulate(std::begin(squares), std::end(squares), 0.0);

  return sum;
}

double gudkov::calcAreaMean(const std::vector< Polygon > &data)
{
  std::vector< double > squares;
  std::transform(std::begin(data), std::end(data), back_inserter(squares), getArea);

  double sum = std::accumulate(std::begin(squares), std::end(squares), 0.0);

  return sum / data.size();
}

double gudkov::calcAreaVertexes(const std::vector< Polygon > &data, size_t vertexes)
{
  std::vector< Polygon > equal;
  std::copy_if(
    std::begin(data),
    std::end(data),
    back_inserter(equal),
    std::bind(isEqualVertexesCount, std::placeholders::_1, vertexes)
  );

  std::vector< double > squares;
  std::transform(std::begin(equal), std::end(equal), back_inserter(squares), getArea);

  double sum = std::accumulate(std::begin(squares), std::end(squares), 0.0);

  return sum;
}

double gudkov::getMaxArea(const std::vector< Polygon > &data)
{
  double area = getArea(*std::max_element(std::begin(data), std::end(data), isLessByArea));

  return area;
}

size_t gudkov::getMaxVertexes(const std::vector< Polygon > &data)
{
  size_t vertexes = std::max_element(
    std::begin(data),
    std::end(data),
    isLessByVertexes
  )->points.size();

  return vertexes;
}

double gudkov::getMinArea(const std::vector< Polygon > &data)
{
  double area = getArea(*std::min_element(std::begin(data), std::end(data), isLessByArea));

  return area;
}

size_t gudkov::getMinVertexes(const std::vector< Polygon > &data)
{
  size_t vertexes = std::min_element(
    std::begin(data),
    std::end(data),
    isLessByVertexes
  )->points.size();

  return vertexes;
}

size_t gudkov::getCountEven(const std::vector< Polygon > &data)
{
  size_t count = std::count_if(std::begin(data), std::end(data), isEvenVertexesCount);

  return count;
}

size_t gudkov::getCountOdd(const std::vector< Polygon > &data)
{
  size_t count = std::count_if(std::begin(data), std::end(data), isOddVertexesCount);

  return count;
}

size_t gudkov::getCountVertexes(const std::vector< Polygon > &data, size_t vertexes)
{
  size_t count = std::count_if(
    std::begin(data),
    std::end(data),
    std::bind(isEqualVertexesCount, std::placeholders::_1, vertexes)
  );

  return count;
}

size_t gudkov::getPermutationsCount(const std::vector< Polygon > &data, const Polygon &polygon)
{
  size_t count = std::count_if(
    std::begin(data),
    std::end(data),
    std::bind(isEqualPolygons, std::placeholders::_1, polygon)
  );

  return count;
}

size_t gudkov::getLessAreaCount(const std::vector< Polygon > &data, const Polygon &polygon)
{
  size_t count = std::count_if(
    std::begin(data),
    std::end(data),
    std::bind(isLessByArea, std::placeholders::_1, polygon)
  );

  return count;
}
