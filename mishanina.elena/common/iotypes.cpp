#include "iotypes.h"
#include <iomanip>

std::istream &mishanina::operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '\0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &mishanina::operator>>(std::istream &in, LongLongIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref >> DelimiterIO{'l'} >> DelimiterIO{'l'};
}

std::istream &mishanina::operator>>(std::istream &in, UnsignedLongLongIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref >> DelimiterIO{'u'} >> DelimiterIO{'l'} >> DelimiterIO{'l'};
}

std::istream &mishanina::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}

std::istream &mishanina::operator>>(std::istream &in, LabelIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (std::size_t i = 0; i < dest.exp.length(); i++)
  {
    in >> DelimiterIO{dest.exp[i]};
  }
  return in;
}

std::ostream &mishanina::operator<<(std::ostream &out, const LongLongIO &dest)
{
  out << ":key1 ";
  out << dest.ref << "ll";
  return out;
}

std::ostream &mishanina::operator<<(std::ostream &out, const UnsignedLongLongIO &dest)
{
  out << ":key2 ";
  out << dest.ref << "ull";
  return out;
}
