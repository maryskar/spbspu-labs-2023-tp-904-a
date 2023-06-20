#include "polygon.h"
#include <iterator>
#include <algorithm>
#include <numeric>
#include <limits>
std::istream &dimkashelk::operator>>(std::istream &in, Polygon &polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
  if (count < 3)
  {
    in.ignore(max_size, '\n');
    in.setstate(std::ios::failbit);
    return in;
  }
  polygon.points.clear();
  std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(polygon.points));
  if (!in)
  {
    in.ignore(max_size, '\n');
    return in;
  }
  std::string endOfLine;
  std::getline(in, endOfLine);
  if (endOfLine.find_first_not_of(' ') != std::string::npos)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}
double dimkashelk::getArea(const Polygon &polygon)
{
  size_t countPoints = polygon.points.size();
  std::vector< double > values(countPoints - 1);
  auto begin_first = polygon.points.begin();
  auto begin_second = begin_first;
  begin_second++;
  auto end = polygon.points.end();
  end--;
  dimkashelk::AreaStorage areaStorage;
  std::transform(begin_first, end, begin_second, std::back_inserter(values), areaStorage);
  double area = std::accumulate(values.begin(), values.end(), 0.0);
  area += areaStorage(polygon.points.back(), polygon.points.front());
  area = std::abs(area) / 2;
  return area;
}
