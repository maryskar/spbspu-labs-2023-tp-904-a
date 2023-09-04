#include "struct_io.h"
#include "iofmt_guard.h"

#include <iostream>
#include <iomanip>

std::istream& operator>>(std::istream& in, delimiter_sep&& dest)
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

std::istream& operator>>(std::istream& in, delimiter_IO&& dest)
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

std::istream& operator>>(std::istream& in, string_IO&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  return std::getline(in >> delimiter_IO{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, DBL_sciIO&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  return in >> dest.ref;
}
std::istream& operator>>(std::istream& in, ULL_hexIO&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
  in >> delimiter_sep{ '0' } >> delimiter_sep{ 'x' } >> std::hex >> dest.ref;
  return in;
}

std::ostream& operator<<(std::ostream& out, const DBL_sciIO& dest)
{
  std::ostream::sentry sent(out);
  if (!sent)
  {
    return out;
  }
}
