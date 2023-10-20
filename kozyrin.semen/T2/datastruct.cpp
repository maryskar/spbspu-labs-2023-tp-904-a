#include "datastruct.h"
#include "streamstuff.h"
using namespace kozyrin;

bool kozyrin::comp(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1) {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2) {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.length() < rhs.key3.length();
}

std::istream& kozyrin::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  DataStruct input;
  using del = DelimiterIO;
  using label = LabelIO;
  using dbl = DoubleIO;
  using ull = UllIO;
  using str = StringIO;

  in >> del{'('};
  for (int i = 0; i < 3; i++) {
    in >> label{":key"};
    int key = 0;
    in >> key;

    if (key == 1) {
      in >> dbl{input.key1};
    }
    if (key == 2) {
      in >> ull{input.key2};
    }
    if (key == 3) {
      in >> str{input.key3};
    }
  }
  return in;
}

std::ostream& kozyrin::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  iofmtguard fmtguard(out);

  out << '(';
  out << ":key1 " << src.key1/100 << "e+2";
  out << ":key2 " << src.key2 << "ull";
  out << ":key3 " << '"' << src.key3 << '"' << ":)";
  return out;
}
