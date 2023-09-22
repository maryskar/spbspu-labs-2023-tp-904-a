#include "TypesIO.h"

#include <cmath>
#include <iomanip>

#include "FormatGuard.h"

std::istream& ganiullin::operator>>(std::istream& in, DelimiterIO&& dest)
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

std::istream& ganiullin::operator>>(std::istream& in, DoubleI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> std::scientific >> dest.ref;
}

std::ostream& ganiullin::operator<<(std::ostream& out, const DoubleO&& dest)
{
  std::ostream::sentry sentry(out);
  iofmtguard iofmtguard(out);
  if (!sentry) {
    return out;
  }

  double value = dest.val;
  int exponent = 0;

  if (value == 0 || std::abs(value) == 1) {
    exponent = 0;
  } else if (std::abs(value) < 1) {
    while (std::abs(value) * 10 < 10) {
      value *= 10;
      exponent--;
    }
  } else {
    while (std::abs(value) / 10 >= 1) {
      value /= 10;
      exponent++;
    }
  }
  return out << std::fixed << std::setprecision(1) << value
             << (exponent < 0 ? "e" : "e+") << exponent;
}

std::istream& ganiullin::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return std::getline(in >> DelimiterIO {'"'}, dest.ref, '"');
}

std::istream& ganiullin::operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  for (size_t i = 0; i < dest.exp.size(); i++) {
    in >> DelimiterIO {dest.exp[i]};
  }
  return in;
}

std::istream& ganiullin::operator>>(std::istream& in, ULongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> LabelIO {"0x"} >> std::hex >> dest.ref;
}
std::ostream& ganiullin::printErrorMessage(std::ostream& out)
{
  return out << "<INVALID COMMAND>";
}
