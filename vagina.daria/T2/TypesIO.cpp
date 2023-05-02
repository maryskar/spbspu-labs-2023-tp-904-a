#include "TypesIO.h"

std::istream &operator>>(std::istream &in, DoubleIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> std::scientific >> dest.num;
}
std::istream& operator >>(std::istream& in, LiteralIO &&dest)
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
std::istream &operator>>(std::istream &in, BinUnsignedLongLongIO &&dest)
{
  std::istream::sentry sentry(in);
  in >> DelimiterIO{ '0' } >> LiteralIO{ "bB" } >> dest.num;
  return in;
}
std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char delim = '0';
  in >> delim;
  if (in && (delim != dest.char_))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream &operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.string, '"');
}