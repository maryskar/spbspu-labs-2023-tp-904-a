#include "data.h"
#include "iostruct.h"
#include "streamsguard.h"
#include <iostream>

namespace chulkov {
  std::string getUllBin(unsigned long long data) {
    unsigned long long var = data;
    std::string res = "";
    while (var)
    {
      res = std::to_string(var % 2) + res;
      var /= 2;
    }
    res = "0b0" + res;
    return res;
  }

  std::istream &operator>>(std::istream &in, Data &dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    Data input; {
      using sep = DelimiterIO;
      using label = LabelIO;
      using chr = CharIO;
      using str = StringIO;
      in >> sep{ '{' };
      in >> label{ "key1" } >> sep{ ':' } >> UllIO{ input.key1 };
      in >> sep{ ',' };
      in >> label{ "key2" } >> sep{ ':' } >> chr{ input.key2 };
      in >> sep{ ',' };
      in >> label{ "key3" } >> sep{ ':' } >> str{ input.key3 };
      in >> sep{ '}' };
    }
    if (in) {
      dest = input;
    }
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const Data &src) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }
    StreamGuard StreamGuard(out);
    auto key1 = getUllBin(src.key1);
    out << "{ ";
    out << "key1" << " " << key1 << "ull" << ":";
    out << "key2" << " " << src.key2 << ":";
    out << "key3" << " " << '"' << src.key3 << '"';
    out << " }";
    return out;
  }

  bool Comparator::operator()(const Data& frst, const Data& sec) {
    if (frst.key1 == sec.key1) {
      if (frst.key2 == sec.key2) {
        return frst.key3.length() < sec.key3.length();
      }
      return frst.key2 < sec.key2;
    }
    else {
      return frst.key1 < sec.key1;
    }
  }
}
