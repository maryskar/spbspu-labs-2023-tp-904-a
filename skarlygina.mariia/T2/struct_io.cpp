#include "struct_io.h"
#include "iofmt_guard.h"

#include <iostream>
#include <iomanip>

std::istream& skarlygina::operator>>(std::istream& in, delimiter_sep_t&& dest)
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

std::istream& skarlygina::operator>>(std::istream& in, delimiter_IO_t&& dest)
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

std::istream& skarlygina::operator>>(std::istream& in, string_IO_t&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  return std::getline(in >> delimiter_IO_t{ '"' }, dest.ref, '"');
}

std::istream& skarlygina::operator>>(std::istream& in, DBL_sciI_t&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  return in >> std::scientific >> dest.ref;
}

std::istream& skarlygina::operator>>(std::istream& in, ULL_hexI_t&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  in >> delimiter_sep_t{ '0' } >> delimiter_sep_t{ 'x' } >> std::hex >> dest.ref;
  return in;
}

std::ostream& skarlygina::operator<<(std::ostream& out, ULL_hexO_t&& dest)
{
  std::ostream::sentry sent(out);
  if (!sent)
  {
    return out;
  }
  return out << "0x" << std::hex << std::uppercase << dest.ref;
}

std::ostream& skarlygina::operator<<(std::ostream& out, const DBL_sciO_t& dest)
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

std::ostream& operator<<(std::ostream& out, const skarlygina::string_IO_t& dest)
{
  std::ostream::sentry sent(out);
  if (!sent)
  {
    return out;
  }
  return out << dest.ref;
}
