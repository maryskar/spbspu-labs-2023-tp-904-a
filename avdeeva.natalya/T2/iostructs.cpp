#include "iostructs.h"
#include <cmath>
std::istream& avdeeva::operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char exp = '\0';
  in >> exp;
  if (in && exp != std::tolower(dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& avdeeva::operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < dest.exp.length(); ++i)
  {
    in >> DelimiterIO{dest.exp[i]};
  }
  return in;
}
std::istream& avdeeva::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'}, dest.exp, '"');
}
std::istream& avdeeva::operator>>(std::istream& in, UnsignedLongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.num >> DelimiterIO{'u'} >> DelimiterIO{'l'} >> DelimiterIO{'l'};
}
std::string avdeeva::convertToScientific(double number)
{
  int degree = 0;
  while (std::abs(number) < 1 && number != 0)
  {
    number *= 10;
    degree--;
  }
  while (std::abs(number) >= 10)
  {
    number /= 10;
    degree++;
  }
  std::string res = std::to_string(number);
  while (res.size() < 4)
  {
    res += '0';
  }
  res = res.substr(0, 4);
  return res + 'e' + std::to_string(degree);
}