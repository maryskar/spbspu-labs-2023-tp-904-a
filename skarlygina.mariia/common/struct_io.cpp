#include "struct_io.h"
#include <iofmt_guard.h>
#include <iostream>
#include <iomanip>

std::istream& skarlygina::operator>>(std::istream& in, DelimiterSep&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  char c = '\0';
  in >> c;
  if (in && (std::tolower(c) != dest.sep))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& skarlygina::operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& skarlygina::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& skarlygina::operator>>(std::istream& in, DBLsciI&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  return in >> std::scientific >> dest.ref;
}

std::istream& skarlygina::operator>>(std::istream& in, ULLhexI&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  in >> DelimiterSep{ '0' } >> DelimiterSep{ 'x' } >> std::hex >> dest.ref;
  return in;
}

std::ostream& skarlygina::operator<<(std::ostream& out, ULLhexO&& dest)
{
  std::ostream::sentry sent(out);
  if (!sent)
  {
    return out;
  }
  return out << "0x" << std::hex << std::uppercase << dest.ref;
}

std::ostream& skarlygina::operator<<(std::ostream& out, const DBLsciO& dest)
{
  std::ostream::sentry sent(out);
  if (!sent)
  {
    return out;
  }

  double sci_dbl = dest.ref;
  int degree = 0;
  while (sci_dbl != 0 && sci_dbl < 1.0)
  {
    sci_dbl = sci_dbl * 10;
    degree--;
  }
  while (sci_dbl != 0 && sci_dbl >= 10.0)
  {
    sci_dbl = sci_dbl / 10;
    degree++;
  }
  Iofmtguard guard(out);
  out << std::fixed << std::setprecision(1) << sci_dbl << "e" << std::showpos << degree;
  return out;
}

std::ostream& operator<<(std::ostream& out, const skarlygina::StringIO& dest)
{
  std::ostream::sentry sent(out);
  if (!sent)
  {
    return out;
  }
  return out << dest.ref;
}
