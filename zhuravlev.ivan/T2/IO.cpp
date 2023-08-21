#include "IO.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <string>
#include <bitset>

using namespace zhuravlev;

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && c != dest.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, HexIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> DelimiterIO{ '0' } >> DelimiterIO{ 'x' } >> std::hex >> dest.ref;
}

std::istream& operator>>(std::istream& in, BinIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::bitset< sizeof(unsigned long long) > value(dest.ref);
  return in >> DelimiterIO{ '0' } >>  DelimiterIO{ 'b' } >>value;
}

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < dest.exp.length(); i++)
  {
    in >> dest.exp[i];
  }
  return in;
}
