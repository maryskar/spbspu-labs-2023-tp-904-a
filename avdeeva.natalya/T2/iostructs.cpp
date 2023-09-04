#include "iostructs.h"
std::istream& avdeeva::operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char exp = '\0';
  in >> exp;
  if (in && exp != std::tolower(dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& avdeeva::operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < dest.exp.length(); ++i)
  {
    in >> DelimiterIO{dest.exp[i]};
  }
  return in;
}
std::istream& avdeeva::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'}, dest.exp, '"');
}