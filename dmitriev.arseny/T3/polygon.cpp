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

bool lessX(dmitriev::Point lhs, dmitriev::Point rhs)
{
  return lhs.x < rhs.x;
}

bool lessY(dmitriev::Point lhs, dmitriev::Point rhs)
{
  return lhs.y < rhs.y;
}

dmitriev::Frame dmitriev::getFrame(const Polygon& polygon)
{
  auto begin = polygon.points.begin();
  auto end = polygon.points.end();

  int minX = std::min_element(begin, end, lessX)->x;
  int maxX = std::max_element(begin, end, lessX)->x;
  int minY = std::min_element(begin, end, lessY)->y;
  int maxY = std::max_element(begin, end, lessY)->y;

  return {{minX, minY}, {maxX, maxY}};
}

dmitriev::Frame correctFrame(dmitriev::Frame result, dmitriev::Frame value)
{
  int minX = lessX(result.first, value.first) ? result.first.x : value.first.x;
  int maxX = lessX(result.second, value.second) ? value.second.x : result.second.x;
  int minY = lessY(result.first, value.first) ? result.first.y : value.first.y;
  int maxY = lessY(result.second, value.second) ? value.second.y : result.second.y;

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

bool dmitriev::isFrameInFrame(const Frame& lhs, const Frame& rhs)
{
  bool case1 = !lessX(lhs.first, rhs.first);
  bool case2 = !lessY(lhs.first, rhs.first);
  bool case3 = !lessX(rhs.second, lhs.second);
  bool case4 = !lessY(rhs.second, lhs.second);

  return case1 && case2 && case3 && case4;
}

dmitriev::Point getDifference(const dmitriev::Point& lhs, const dmitriev::Point& rhs)
{
  return {rhs.x - lhs.x, rhs.y - lhs.y};
}

bool compareDifference(const dmitriev::Point& lhs, const dmitriev::Point& rhs)
{
  return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

bool dmitriev::isSame(Polygon lhs, Polygon rhs)
{
  if (getSize(lhs) != getSize(rhs))
  {
    return false;
  }

  std::sort(lhs.points.begin(), lhs.points.end(), lessX);
  std::sort(lhs.points.begin(), lhs.points.end(), lessY);
  std::sort(rhs.points.begin(), rhs.points.end(), lessX);
  std::sort(rhs.points.begin(), rhs.points.end(), lessY);

  std::vector< Point > lhsDifferences;
  std::transform(lhs.points.begin(),
    lhs.points.end() - 1,
    lhs.points.begin() + 1,
    std::back_inserter(lhsDifferences),
    getDifference);

  std::vector< Point > rhsDifferences;
  std::transform(rhs.points.begin(),
    rhs.points.end() - 1,
    rhs.points.begin() + 1,
    std::back_inserter(rhsDifferences),
    getDifference);

  bool result = std::equal(lhsDifferences.begin(),
    lhsDifferences.end(),
    rhsDifferences.begin(),
    compareDifference);

  return result;
}
//команды + опраторы== + 