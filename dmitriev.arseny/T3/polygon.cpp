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
