#include "TypesIO.h"

#include <cmath>
#include <iomanip>

std::istream& ovsyannikov::operator>>(std::istream& in, ovsyannikov::DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
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

std::istream& ovsyannikov::operator>>(std::istream& in, ovsyannikov::StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> ovsyannikov::DelimiterIO{'"'}, dest.ref, '"');
}

std::istream& ovsyannikov::operator>>(std::istream& in, ovsyannikov::LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < dest.exp.size(); i++)
  {
    in >> ovsyannikov::DelimiterIO{dest.exp[i]};
  }
  return in;
}

std::istream& ovsyannikov::operator>>(std::istream& in, ovsyannikov::ULongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> ovsyannikov::LabelIO{"0x"} >> std::hex >> dest.ref;
}

std::istream& ovsyannikov::operator>>(std::istream& in, CharIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> ovsyannikov::LabelIO{"'"} >> dest.ref >> ovsyannikov::LabelIO{"'"};
}
