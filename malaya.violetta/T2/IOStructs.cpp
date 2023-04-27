#include<iostream>
#include"IOStructs.hpp"
std::istream & malaya::operator>>(std::istream & in, DelimiterIO && dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  std::string input = " ";
  in >> input;
  if (in && (input != dest.expression))
  {
    in.setstate(std::ios::failbit);
  }
}
std::istream & malaya::operator>>(std::istream & in, DoubleIO && dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  in >> dest.reference >> DelimiterIO{"d"};
  return in;
}
std::istream & malaya::operator>>(std::istream & in, UnsignedLongLongIO && dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  in >> dest.reference >> DelimiterIO{"ull"};
  return in;
}
std::istream & malaya::operator>>(std::istream & in, StringIO && dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{"\""}, dest.reference, '"');
}
std::istream & malaya::operator>>(std::istream & in, LabelIO && dest)
{
  std::istream::sentry istreamChecker(in);
  if (!istreamChecker)
  {
    return in;
  }
  char input[4] {" "};
  //in >> input;
  in.getline(input, 3);
  //if ((in >> StringIO{input}) && (input != dest.expression)) //fsfsdfdsfds
  if (in && (input != dest.expression))
  {
    in.setstate(std::ios::failbit);
  }
}
