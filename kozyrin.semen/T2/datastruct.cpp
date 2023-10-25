#include "datastruct.h"
#include <iomanip>
#include <iterator>
#include <algorithm>
#include "iostuff.h"
#include "fmtguard.h"

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

struct Double {
  double x;
};

namespace kozyrin {
  std::ostream& operator<<(std::ostream& out, const Double& n)
  {
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }
    iofmtguard fmtguard(out);
    int exp = 0;
    double base = n.x;
    while (base >= 10 or base < 1) {
      if (base >= 10) {
        base /= 10;
        exp++;
      } else if (base < 1) {
        base *= 10;
        exp -= 1;
      } else {
        break;
      }
    }
    std::string sign = "e";
    if (exp > 0) {
      sign += '+';
    }
    return out << std::fixed << std::setprecision(1) << base << sign << exp;
  }
}

std::ostream& kozyrin::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  iofmtguard fmtguard(out);
  out << '(';
  out << ":key1 " << Double{src.key1};
  out << ":key2 " << src.key2 << "ull";
  out << ":key3 " << '"' << src.key3 << '"' << ":)";
  return out;
}
