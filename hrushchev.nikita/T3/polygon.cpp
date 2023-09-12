#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <iotypes.hpp>

bool hrushchev::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x_ == rhs.x_) && (lhs.y_ == rhs.y_);
}

bool hrushchev::operator==(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points_ == rhs.points_;
}

std::istream& hrushchev::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{'('};
  in >> dest.x_;
  in >> DelimiterIO{';'};
  in >> dest.y_;
  in >> DelimiterIO{')'};
  return in;
}

std::istream& hrushchev::operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t num_of_points = 0;
  in >> num_of_points;
  if (num_of_points < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest.points_.clear();
  std::vector< Point > temp_points(num_of_points);
  std::istream_iterator< Point > point_iter(in);
  std::copy_n(point_iter, num_of_points, temp_points.begin());
  if (temp_points.size() != num_of_points)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest.points_.swap(temp_points);
  return in;
}
