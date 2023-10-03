#include "iotypes.h"
#include <iomanip>
#include "iofmtguard.h"

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

std::istream &fesenko::operator>>(std::istream &in, DoubleI &&dest)
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
  char c = '\'';
  return in >> DelimiterIO{ c } >> dest.ref >> DelimiterIO{ c };
}

std::istream &fesenko::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '"';
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

std::ostream &fesenko::operator<<(std::ostream &out, DoubleO &&dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  iofmtguard fmtguard(out);
  double val = dest.val;
  int exp = 0;
  if (val == 0 || std::abs(val) == 1) {
    exp = 0;
  } else if (std::abs(val) < 1) {
    while (std::abs(val) * 10 < 10) {
      val *= 10;
      exp--;
    }
  } else {
    while (std::abs(val) / 10 >= 1) {
      val /= 10;
      exp++;
    }
  }
  return out << std::fixed << std::setprecision(1) << val << (exp < 0 ? "e" : "e+") << exp;
}
