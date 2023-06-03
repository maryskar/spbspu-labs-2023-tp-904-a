#include "IOStructs.hpp"
#include <iostream>
std::istream & malaya::operator>>(std::istream & in, DelimiterIO && dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  char input = '0';
  in >> input;
  if (in && (input != dest.expression))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream & malaya::operator>>(std::istream & in, DoubleIO && dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  in >> dest.reference >> DelimiterIO{'d'};
  return in;
}
std::istream & malaya::operator>>(std::istream & in, UnsignedLongLongIO && dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  in >> std::oct >> dest.reference;
  return in;
}
std::istream & malaya::operator>>(std::istream & in, StringIO && dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'}, dest.reference, '"');
}
std::istream & malaya::operator>>(std::istream & in, LabelIO && dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  for (size_t i = 0; i < dest.expression.length(); i++)
  {
    in >> DelimiterIO{dest.expression[i]};
  }
  return in;
}
