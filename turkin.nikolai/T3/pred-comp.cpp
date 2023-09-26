#include "pred-comp.hpp"
#include "data-structs.hpp"

#include <algorithm>
#include <numeric>
#include <vector>

bool turkin::isOdd::operator()(const Polygon & rhs)
{
  return rhs.points.size() % 2 != 0;
}

bool turkin::isEven::operator()(const Polygon & rhs)
{
  return rhs.points.size() % 2 == 0;
}

turkin::isNum::isNum(std::size_t num):
  num_(num)
{}

bool turkin::isNum::operator()(const Polygon & rhs)
{
  return rhs.points.size() == num_;
}

bool turkin::isSizeLess::operator()(const Polygon & lhs, const Polygon & rhs)
{
  return lhs.points.size() < rhs.points.size();
}

bool turkin::isSizeGreater::operator()(const Polygon & lhs, const Polygon & rhs)
{
  return lhs.points.size() > rhs.points.size();
}

bool turkin::isAreaLess::operator()(const Polygon & lhs, const Polygon & rhs)
{
  return calcArea(0.0, lhs) < calcArea(0.0, rhs);
}

bool turkin::isAreaGreater::operator()(const Polygon & lhs, const Polygon & rhs)
{
  return calcArea(0.0, lhs) > calcArea(0.0, rhs);
}

namespace
{
  std::vector< turkin::Point > sub;
  bool calcAngle(std::size_t it, std::size_t index)
  {
    turkin::Point a = sub[index];
    turkin::Point b = sub[(index + 1) % sub.size()];
    turkin::Point c = sub[(index + 2) % sub.size()];
    return it + ((b.x - a.x) * (c.x - b.x) + (b.y - a.y) * (c.y - b.y) == 0);
  }
}

bool turkin::isRightAngle::operator()(const Polygon & rhs)
{
  sub = rhs.points;
  std::vector< std::size_t > indexes(sub.size());
  std::iota(indexes.begin(), indexes.end(), 0);
  bool result = std::accumulate(indexes.begin(), indexes.end(), 0, calcAngle);
  return result;
}


