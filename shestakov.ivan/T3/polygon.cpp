#include "polygon.h"
#include <algorithm>
#include <iterator>

namespace shestakov
{
  bool operator==(const Point& lhs, const Point& rhs)
  {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
  }
  bool operator==(const Polygon& lhs, const Polygon& rhs)
  {
    return std::equal(lhs.points.begin(), lhs.points.end(), rhs.points.begin());
  }
  std::istream& operator>>(std::istream &in, DelimeterIO &&dest)
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
  std::istream& operator>>(std::istream &in, Point &rhs)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
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
  std::istream& operator>>(std::istream &in, Polygon &rhs)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Polygon input;
    size_t points = 0;
    in >> points;
    if (points < 3)
    {
      in.setstate(std::ios::failbit);
    }
    input.points.reserve(points);
    std::copy_n(std::istream_iterator<Point>(in), points - 1, std::back_inserter(input.points));
    char chr = '0';
    in.get(chr);
    if (chr != '\n')
    {
      std::copy_n(std::istream_iterator<Point>(in), 1, std::back_inserter(input.points));
    }
    else
    {
      throw std::logic_error("");
    }
    if (in)
    {
      std::string temp = "";
      std::getline(in, temp);
      if (temp.empty())
      {
        rhs.points.swap(input.points);
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    return in;
  }
}
