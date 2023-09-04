#include "TypesIO.h"

#include <cmath>
#include <iomanip>
#include "FormatGuard.h"

std::istream& ganiullin::operator>>(std::istream& in, EntryI&& dest)
{
  std::istream::sentry sentry(in);
  in >> dest.ref >> dest.val;
  return in;
}
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
std::istream& ganiullin::operator>>(std::istream& in, ganiullin::WordIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  in >> dest.ref;
  char a = '\0';
  a = dest.ref.front();
  while (!isalnum(a) && a != '\0') {
    dest.ref.erase(0, 1);
    a = dest.ref.front();
  }
  a = dest.ref.back();
  while (!isalnum(a) && a != '\0') {
    dest.ref.erase(dest.ref.size() - 1, 1);
    a = dest.ref.back();
  }
  dest.ref.shrink_to_fit();
  for (size_t i = 0; i < dest.ref.size(); i++) {
    dest.ref[i] = std::tolower(dest.ref[i]);
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
  for (size_t i = 0; i < dest.exp.size(); i++) {
    in >> ganiullin::DelimiterIO {dest.exp[i]};
  }
  return in;
}

std::istream& ganiullin::operator>>(std::istream& in, ganiullin::ULongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> ganiullin::LabelIO {"0x"} >> std::hex >> dest.ref;
}
