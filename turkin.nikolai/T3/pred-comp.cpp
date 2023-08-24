#include "pred-comp.hpp"

bool turkin::isOdd::operator()(const Polygon & rhs)
{
  return rhs.points.size() % 2 == 0;
}

bool turkin::isEven::operator()(const Polygon & rhs)
{
  return rhs.points.size() % 2 != 0;
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
