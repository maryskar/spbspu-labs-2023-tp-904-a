#include "dataStruct.h"
#include <iomanip>
#include "iotypes.h"
#include "iofmtguard.h"

bool fesenko::compare(const DataStruct &first, const DataStruct &second)
{
  if (first.key1 != second.key1) {
    return first.key1 < second.key1;
  } else if (first.key2 != second.key2) {
    return first.key2 < second.key2;
  } else {
    return first.key3.length() < second.key3.length();
  }
}

std::istream &fesenko::operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  DataStruct input;
  using sep = DelimiterIO;
  using lbl = LabelIO;
  using dbl = DoubleI;
  using chr = CharIO;
  using str = StringIO;
  in >> sep{ '(' } >> sep{ ':' };
  for (size_t i = 0; i < 3; i++) {
    size_t num = 0;
    in >> lbl{ "key" } >> num;
    if (num == 1) {
      in >> dbl{ input.key1 } >> sep{ ':' };
    } else if (num == 2) {
      in >> chr{ input.key2 } >> sep{ ':' };
    } else if (num == 3) {
      in >> str{ input.key3 } >> sep{ ':' };
    } else {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  in >> sep{')'};
  if (in) {
    dest = input;
  }
  return in;
}

std::ostream &fesenko::operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(";
  out << ":key1 " << fesenko::DoubleO{ src.key1 };
  out << ":key2 \'" << src.key2 << "\'";
  out << ":key3 \"" << src.key3;
  out << "\":)";
  return out;
}
