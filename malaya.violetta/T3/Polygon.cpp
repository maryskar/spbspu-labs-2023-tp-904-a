#include "Polygon.hpp"
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

std::istream & malaya::operator>>(std::istream & in, SeparatorPointIO && separator)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  char input = '0';
  in >> input;
  if (in && (input != separator.sep))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & malaya::operator>>(std::istream & in, Point & point)
{
  in >> SeparatorPointIO{'('};
  in >> point.x;
  in >> SeparatorPointIO{';'};
  in >> point.y;
  in >> SeparatorPointIO{')'};
}

std::istream & malaya::operator>>(std::istream & in, Polygon & polygon)
{
  size_t pointNumber = 0;
  std::string str;
  std::getline(in, str, '\n');
  std::istringstream stream(str);
  stream >> pointNumber;
  std::copy(std::istream_iterator< malaya::Point >(stream),
    std::istream_iterator< malaya::Point >(),
        std::back_inserter(polygon.points));
}