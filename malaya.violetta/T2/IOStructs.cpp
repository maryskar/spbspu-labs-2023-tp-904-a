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
std::istream & malaya::operator>>(std::istream & in, LabelIO & dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  std::string input = " ";
  if (in >> input)
  {
    if (input.size() == 4 && input[0] == 'k' && input[1] == 'e' && input[2] == 'y')
    {
      int keyNumber = static_cast< int >(input[3]) - 48;
      if (keyNumber >= 1 && keyNumber <= 3)
      {
        dest.expression = input;
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
