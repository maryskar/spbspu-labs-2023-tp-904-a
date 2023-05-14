#include "point.h"
#include <iostream>
std::istream &checkSentry(std::istream &in)
{
  std::istream::sentry sentry(in);
  return in;
}
std::istream &operator>>(std::istream &in, Point &dest)
{
  if (!checkSentry(in))
  {
    return in;
  }
  char openParenthesis = '(';
  char comma = ';';
  char closeParenthesis = ')';
  return in >> openParenthesis >> dest.x >> comma >> dest.y >> closeParenthesis;
}