#include "polygon.h"
#include <algorithm>
#include <numeric>
#include <limits>
#include <functional>
#include <iterator>

std::istream & shestakov::operator>>(std::istream & in, DelimeterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream & shestakov::operator>>(std::istream & in, Point & rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry){
    return in;
  }
  Point input{0, 0};
  using del = DelimeterIO;
  in >> del{'('} >> input.x >> del{';'} >> input.y >> del{')'};
  if (in)
  {
    rhs = input;
  }
  return in;
}
std::istream & shestakov::operator>>(std::istream & in, Polygon & rhs)
{
  std::istream::sentry sentry(in);
  if(!sentry){
    return in;
  }
  Polygon input;
  size_t points = 0;
  in >> points;
  if(points < 3){
    in.setstate(std::ios::failbit);
  }
  input.points.reserve(points);
  std::copy_n(std::istream_iterator< Point >(in), points, std::back_inserter(input.points));
  if (in)
  {
    rhs.points.swap(input.points);
  }
  return in;
}
