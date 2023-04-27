#ifndef DATA_H
#define DATA_H

#include <iomanip>
#include <limits>

#include "FormatGuard.h"
#include "TypesIO.h"

constexpr size_t CHARS_TO_IGNORE = std::numeric_limits<std::streamsize>::max();

// DBL SCI - double     ULL HEX- unsigned long long
struct DataStruct {
  double key1;
  unsigned long long key2;
  std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterIO;
    using label = LabelIO;
    using dbl = DoubleIO;
    using str = StringIO;
    using ull = ULongLongIO;
    size_t labelNum = 0;

    in >> sep{'('};
    for (size_t i = 0; (i < 3) && in; i++) {
      in >> sep{':'} >> label{"key"} >> labelNum;
      switch (labelNum) {
        case 1:
          in >> dbl{input.key1};
          break;
        case 2:
          in >> ull{input.key2};
          break;
        case 3:
          in >> str{input.key3};
          break;
        default:
          in.setstate(std::ios::failbit);
          break;
      }
    }
    // in >> label{"key1"} >> sep{':'} >> dbl{input.key1};
    // in >> sep{','};
    // in >> label{"key2"} >> sep{':'} >> ull{input.key2};
    // in >> sep{','};
    // in >> label{"key3"} >> sep{':'} >> str{input.key3};
    in >> sep{':'};
    in >> sep{')'};
  }

  if (in) {
    dest = input;
  } else {
    in.clear();
    in.ignore(CHARS_TO_IGNORE, '(');
    in.putback('(');
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }

  iofmtguard fmtguard(out);
  out << "(:";

  out << "key1" << ' ' << std::scientific << src.key1 << ':';
  out << "key2" << ' ' << "0x" << std::hex << std::uppercase << src.key2 << ':';
  out << "key3" << ' ' << '"' << src.key3 << '"' << ':';
  out << ')';
  return out;
}
#endif
