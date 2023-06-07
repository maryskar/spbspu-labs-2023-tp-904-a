#include "polygon.h"
#include <iterator>
#include <algorithm>
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
  std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(polygon.points));
  return in;
}
double dimkashelk::getArea(const dimkashelk::Polygon &polygon)
{
  size_t countPoints = polygon.points.size();
  std::vector< double > values(countPoints);
  auto begin = polygon.points.begin();
  auto end = polygon.points.end();
  --end;
  AreaStorage areaStorage;
  std::transform(begin, end, ++begin, values.begin(), areaStorage);
  return areaStorage(polygon.points[countPoints - 1], polygon.points[0]);
}
