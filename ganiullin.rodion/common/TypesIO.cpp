#include "TypesIO.h"

#include <cmath>
#include <iomanip>
#include "FormatGuard.h"

using OutS = std::ostream;
using InS = std::istream;

InS& ganiullin::operator>>(InS& in, EntryI&& dest)
{
  InS::sentry sentry(in);
  in >> WordIO{dest.ref} >> dest.val;
  return in;
}
InS& ganiullin::operator>>(InS& in, DelimiterIO&& dest)
{
  InS::sentry sentry(in);
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
InS& ganiullin::operator>>(InS& in, WordIO&& dest)
{
  InS::sentry sentry(in);
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
InS& ganiullin::operator>>(InS& in, DoubleI&& dest)
{
  InS::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> std::scientific >> dest.ref;
}

OutS& ganiullin::operator<<(OutS& out, const DoubleO&& dest)
{
  OutS::sentry sentry(out);
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

InS& ganiullin::operator>>(InS& in, StringIO&& dest)
{
  InS::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}

InS& ganiullin::operator>>(InS& in, LabelIO&& dest)
{
  InS::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  for (size_t i = 0; i < dest.exp.size(); i++) {
    in >> DelimiterIO{dest.exp[i]};
  }
  return in;
}

InS& ganiullin::operator>>(InS& in, ULongLongIO&& dest)
{
  InS::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> LabelIO{"0x"} >> std::hex >> dest.ref;
}
OutS& ganiullin::operator<<(OutS& out, const EntryO&& dest)
{
  out << '"' << dest.ref.first << "\" " << dest.ref.second;
  return out;
}
