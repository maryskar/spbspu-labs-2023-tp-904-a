#include "polygon.h"
#include <iterator>
#include <algorithm>
#include <numeric>
#include "area_storage.h"
std::istream &dimkashelk::operator>>(std::istream &in, dimkashelk::Polygon &polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  polygon.points.clear();
  std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(polygon.points));
  return in;
}
double dimkashelk::getArea(const dimkashelk::Polygon &polygon)
{
  size_t countPoints = polygon.points.size();
  std::vector< double > values;
  auto begin_first = polygon.points.begin();
  auto begin_second = begin_first;
  begin_second++;
  auto end = polygon.points.end();
  end--;
  dimkashelk::AreaStorage areaStorage;
  std::transform(begin_first, end, begin_second, std::back_inserter(values), areaStorage);
  double area = std::accumulate(values.begin(), values.end(), 0.0);
  area += areaStorage(polygon.points[countPoints - 1], polygon.points[0]);
  area = std::abs(area) / 2;
  return area;
}
