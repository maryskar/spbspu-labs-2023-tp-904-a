#include "streamstuff.h"
#include <math.h>
using namespace kozyrin;

std::istream& kozyrin::operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '0';
  if (in >> c && c != dest.chr) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& kozyrin::operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  for (size_t i = 0; i < dest.str.length(); i++) {
    in >> DelimiterIO{dest.str[i]};
  }
  return in;
}

std::istream& kozyrin::operator>>(std::istream& in, DoubleIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  double base = 0;
  int exp = 0;
  in >> base >> DelimiterIO{'d'} >> exp;

  dest.val = base * pow(10, exp);
  return in;
}

std::istream& kozyrin::operator>>(std::istream& in, UllIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  in >> dest.val >> LabelIO{"ull"};
  return in;
}

std::istream& kozyrin::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'}, dest.str, '"');
}

kozyrin::iofmtguard::iofmtguard(std::basic_ios< char > & s):
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{}

kozyrin::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}

