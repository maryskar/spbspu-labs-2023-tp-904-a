#include "TypesIO.h"
#include <iomanip>
#include <iterator>

std::istream& vagina::operator>>(std::istream &in, DoubleI &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> std::scientific >> dest.num;
}
std::ostream& vagina::operator<<(std::ostream &out, const DoubleO &&dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  double num = dest.num;
  int exp = 0;
  while (num < 1 || num >= 10)
  {
    if (num <= 1)
    {
      num *= 10;
      exp --;
    }
    else if (num >= 1)
    {
      num /= 10;
      exp ++;
    }
  }
  return out << std::fixed << std::setprecision(1) << num << (exp > 0 ? "e+" : "e") << exp;
}
std::istream& vagina::operator>>(std::istream& in, LiteralIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (dest.literal.find(c) == std::string::npos))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& vagina::operator>>(std::istream &in, BinUnsignedLongLongIO &&dest)
{
  in >> DelimiterIO{ '0' } >> LiteralIO{ "bB" };
  unsigned long long num = 0;
  in >> num;
  unsigned long long res = 0;
  int pow = 1;
  while (num != 0)
  {
    if (num % 10 == 1 || num % 10 == 0)
    {
      res += num % 10 * pow;
      pow *= 2;
      num /= 10;
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  dest.num = res;
  return in;
}
std::istream& vagina::operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char delim = '0';
  in >> delim;
  if (in && (delim != dest.symbol))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& vagina::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.string, '"');
}
std::istream& vagina::operator>>(std::istream &in, LabelIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string str = "";
  std::getline(in, str, 'y');
  str += 'y';
  if (in && (str != dest.label))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
