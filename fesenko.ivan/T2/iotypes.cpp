#include "iotypes.h"
#include <iomanip>

std::istream &fesenko::operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &fesenko::operator>>(std::istream &in, DoubleIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> std::scientific >> dest.ref;
}

std::istream &fesenko::operator>>(std::istream &in, CharIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  int quoteCode = 39;
  char c = quoteCode;
  return in >> DelimiterIO{ c } >> dest.ref >> DelimiterIO{ c };
}

std::istream &fesenko::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  int doubleQuoteCode = 34;
  char c = doubleQuoteCode;
  return std::getline(in >> DelimiterIO{ c }, dest.ref, c);
}

std::istream &fesenko::operator>>(std::istream &in, LabelIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  for (size_t i = 0; i < dest.exp.length(); i++) {
    in >> DelimiterIO{ dest.exp[i] };
  }
  return in;
}
