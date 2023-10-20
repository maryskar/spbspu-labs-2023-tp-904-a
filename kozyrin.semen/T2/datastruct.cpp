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

  in >> label{"(:"};
  for (int i = 0; i < 3; i++) {
    in >> label{"key"};
    int key = 0;
    in >> key;

    if (key == 1) {
      in >> dbl{input.key1};
    }
    if (key == 2) {
      in >> ull{input.key2};
      in >> del{':'};
    }
    if (key == 3) {
      in >> str{input.key3};
      in >> del{':'};
    }
  }
  dest = input;
  return in;
}

std::string formatDouble(double n)
{
  int exp = 0;
  while (true) {
    if (n >= 10) {
      n /= 10;
      exp++;
    } else if (n < 1) {
      n *= 10;
      exp -= 1;
    } else {
      break;
    }
  }
  const char* sign = "e";
  if (exp > 0) {
    sign += '+';
  }
  std::string res = std::to_string(n) + sign + std::to_string(exp);
  return res;
}

std::ostream& kozyrin::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  iofmtguard fmtguard(out);
  out << '(';
  out << ":key1 " << formatDouble(src.key1);
  out << ":key2 " << src.key2 << "ull";
  out << ":key3 " << '"' << src.key3 << '"' << ":)";
  return out;
}
