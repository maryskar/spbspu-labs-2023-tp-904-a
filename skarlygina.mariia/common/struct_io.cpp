#include "struct_io.h"
#include <istream>

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
