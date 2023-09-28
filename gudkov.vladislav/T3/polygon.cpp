#include "polygon.h"
#include <algorithm>
#include <numeric>
#include <iterator>
#include <cmath>
#include "scopeGuard.h"
#include "typesIO.h"

static size_t index = 0;

double gudkov::getSide(const Point &a, const Point &b)
{
  return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

double gudkov::getTriangleArea(const Point &a, const Point &b, const Point &c)
{
  double ab = getSide(a, b);
  double bc = getSide(b, c);
  double ac = getSide(c, a);
  double p = (ab + bc + ac) / 2;

  return std::sqrt(p * (p - ab) * (p - bc) * (p - ac));
}

bool gudkov::isSecond(const Point &)
{
  bool isSecondPoint = false;

  if (index % 2 == 0)
  {
    isSecondPoint = true;
  }

  index++;

  return isSecondPoint;
}

double gudkov::getTriangleAreaForArrayOnly(const Point &point)
{
  const Point *address = &point;

  double area = 0.0;

  if (isSecond(point))
  {
    area = getTriangleArea(address[0], address[1], address[2]);
  }

  return area;
}

double gudkov::getArea(const Polygon &polygon)
{
  const std::vector< Point > &points = polygon.points;
  const size_t &n = points.size();

  if (n < 3)
  {
    return 0.0;
  }

  std::vector< double > areas;
  index = 0;
  std::transform(
    std::begin(points),
    std::end(points) - 2,
    std::back_inserter(areas),
    getTriangleAreaForArrayOnly
  );

  double area = std::accumulate(std::begin(areas), std::end(areas), 0.0);

  Polygon inner;
  index = 0;
  std::copy_if(
    std::begin(points),
    std::end(points) - 2,
    std::back_inserter(inner.points),
    isSecond
  );

  if (n % 2 == 0)
  {
    area += getTriangleArea(points[n - 2], points[n - 1], points[0]);
    inner.points.push_back(points[n - 2]);
  }
  else
  {
    inner.points.push_back(points[n - 1]);
  }

  area += getArea(inner);

  return area;
}

std::istream &gudkov::operator>>(std::istream &in, Point &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  iofmtguard fmtguard(in);

  in.unsetf(std::ios_base::skipws);

  in >> DelimiterExpIO{ ' ' };
  Point input;
  {
    in >> DelimiterExpIO{ '(' };
    in >> input.x;
    in >> DelimiterExpIO{ ';' };
    in >> input.y;
    in >> DelimiterExpIO{ ')' };
  }

  if (in)
  {
    dest = input;
  }

  return in;
}

std::istream &gudkov::operator>>(std::istream &in, Polygon &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  iofmtguard fmtguard(in);
  in.unsetf(std::ios_base::skipws);

  Polygon input;

  {
    size_t n = 0;
    in >> n;

    if (in)
    {
      std::copy_n(std::istream_iterator< Point >(in), n, std::back_inserter(input.points));
    }

    if (input.points.size() < 3)
    {
      in.setstate(std::ios::failbit);
    }
  }

  if (in)
  {
    dest = input;

    in >> DelimiterExpIO{ '\n' };

    if (in.eof())
    {
      in.clear();
    }
  }

  return in;
}
