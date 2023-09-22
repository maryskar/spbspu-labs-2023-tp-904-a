#include "polygon.h"
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
