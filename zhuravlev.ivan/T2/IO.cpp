#include "IO.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <bitset>

std::istream& operator>>(std::istream& in, zhuravlev::DelimiterIO&& dest)
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

std::istream& operator>>(std::istream& in, zhuravlev::HexIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> std::hex >> dest.ref;
}

std::istream& operator>>(std::istream& in, zhuravlev::BinIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::bitset< sizeof(unsigned long long) > value(dest.ref);
  return in >> zhuravlev::DelimiterIO{ '0b' } >> value;
}

std::istream& operator>>(std::istream& in, zhuravlev::StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> zhuravlev::DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, zhuravlev::LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < dest.exp.length(); i++)
  {
    in >> zhuravlev::DelimiterIO{dest.exp[i]};
  }
  return in;
}
