#include "TypesIO.h"
#include <bitset>
#include <iomanip>
#include <vector>
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
std::ostream &vagina::operator<<(std::ostream &out, const DoubleO&&dest)
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
std::istream& vagina::operator>>(std::istream &in, BinUnsignedLongLongI &&dest)
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
std::ostream &vagina::operator<<(std::ostream &out, const BinUnsignedLongLongO&&dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  unsigned long long num = dest.num;
  std::vector < unsigned long long > vect;
  int i = 0;
  while (num)
  {
    vect.push_back(num % 2);
    num /= 2;
    i++;
  }
  out << "0b";
  std::copy(vect.rbegin(), vect.rend(), std::ostream_iterator< int >(out));
  if (!vect.empty() == 0)
  {
    out << "0";
  }
  return out;
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
