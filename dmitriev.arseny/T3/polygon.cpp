#include "polygon.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <customtypes.h>

std::istream& dmitriev::operator>>(std::istream& inp, Point& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  inp >> SeparatorIO{'('} >> data.x >> SeparatorIO{';'} >> data.y >> SeparatorIO{')'};
  return inp;
}

std::istream& dmitriev::operator>>(std::istream& inp, Polygon& data)
{
  std::istream::sentry sentry(inp);
  if (!sentry)
  {
    return inp;
  }

  size_t pointsNumber = 0;
  inp >> pointsNumber;

  if (pointsNumber < 3)
  {
    inp.setstate(std::ios::failbit);
    return inp;
  }

  Polygon newData;
  newData.points.reserve(pointsNumber);
  std::copy_n(std::istream_iterator< Point >(inp), pointsNumber, std::back_inserter(newData.points));

  if (inp)
  {
    data.points.swap(newData.points);
  }

  return inp;
}

size_t dmitriev::getSize(const Polygon& polygon)
{
  return polygon.points.size();
}

int getTriangleArea(const dmitriev::Point& lhs, const dmitriev::Point& rhs)
{
  return (lhs.x * rhs.y) - (rhs.x * lhs.y);
}

double dmitriev::getArea(const Polygon& polygon)
{
  std::vector< double > slopes;
  slopes.reserve(getSize(polygon) - 1);
  slopes.push_back(getTriangleArea(polygon.points.front(), polygon.points.back()));
  std::transform(polygon.points.begin(),
    polygon.points.end() - 1,
    polygon.points.begin() + 1,
    std::back_inserter(slopes),
    getTriangleArea);

  return std::abs(std::accumulate(slopes.begin(), slopes.end(), 0.0) / 2.0);
}

bool compareX(dmitriev::Point lhs, dmitriev::Point rhs)
{
  return lhs.x < rhs.x;
}

bool compareY(dmitriev::Point lhs, dmitriev::Point rhs)
{
  return lhs.y < rhs.y;
}

dmitriev::Frame dmitriev::getFrame(const Polygon& polygon)
{
  auto begin = polygon.points.begin();
  auto end = polygon.points.end();

  int minX = std::min_element(begin, end, compareX)->x;
  int maxX = std::max_element(begin, end, compareX)->x;
  int minY = std::min_element(begin, end, compareY)->y;
  int maxY = std::max_element(begin, end, compareY)->y;

  return {{minX, minY}, {maxX, maxY}};
}

dmitriev::Frame correctFrame(dmitriev::Frame result, dmitriev::Frame value)
{
  int minX = compareX(result.first, value.first) ? result.first.x : value.first.x;
  int maxX = compareX(result.second, value.second) ? value.second.x : result.second.x;
  int minY = compareY(result.first, value.first) ? result.first.y : value.first.y;
  int maxY = compareY(result.second, value.second) ? value.second.y : result.second.y;

  return {{minX, minY}, {maxX, maxY}};
}

dmitriev::Frame dmitriev::getPolygonsFrame(std::vector< Polygon > data)
{
  auto begin = data.begin();
  auto end = data.end();

  std::vector< dmitriev::Frame > frames;
  std::transform(begin, end, std::back_inserter(frames), dmitriev::getFrame);

  dmitriev::Frame frame = *frames.begin();
  return std::accumulate(frames.begin() + 1, frames.end(), frame, correctFrame);
}
