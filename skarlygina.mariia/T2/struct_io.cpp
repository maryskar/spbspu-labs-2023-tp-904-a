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
}
std::istream& operator>>(std::istream& in, string_IO&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
}
std::istream& operator>>(std::istream& in, DBL_sciIO&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
}
std::istream& operator>>(std::istream& in, ULL_hexIO&& dest)
{
  std::istream::sentry sent(in);
  if (!sent)
  {
    return in;
  }
}

std::ostream& operator<<(std::ostream& out, const DBL_sciIO& dest);
