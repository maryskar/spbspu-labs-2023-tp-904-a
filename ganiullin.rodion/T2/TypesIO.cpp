#include "TypesIO.h"

#include <cmath>
#include <iomanip>

std::istream& ganiullin::operator>>(std::istream& in, ganiullin::DelimiterIO&& dest)
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

std::istream& ganiullin::operator>>(std::istream& in, ganiullin::DoubleI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> std::scientific >> dest.ref;
}

std::ostream& ganiullin::operator<<(std::ostream& out, const ganiullin::DoubleO&& dest)
{
  std::ostream::sentry sentry(out);
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
  return out << std::fixed << std::setprecision(1) << value << (exponent < 0 ? "e" : "e+") << exponent;
}

std::istream& ganiullin::operator>>(std::istream& in, ganiullin::StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return std::getline(in >> ganiullin::DelimiterIO {'"'}, dest.ref, '"');
}

std::istream& ganiullin::operator>>(std::istream& in, ganiullin::LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  std::string data = "";
  in >> data;
  in.putback(data.back());
  data.pop_back();
  if (in && (data != dest.exp)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& ganiullin::operator>>(std::istream& in, ganiullin::ULongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> ganiullin::DelimiterIO {'0'} >> ganiullin::DelimiterIO {'x'} >> std::hex >> dest.ref;
}
